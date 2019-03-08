#include "Question2FloorHint.h"
#include "QuestionManager.h"
#include "Question2Sphere.h"
#include "CollideManager.h"

#include "Drawer.h"

const char* TEST_TEXTURE = "Game/Texture/ElevatorTexture.png";

Question2FloorHint::Question2FloorHint( QuestionManagerConstPtr question_manager, CollideManagerPtr collide_manager, FLOOR floor ) :
_floor( floor ),
_collide_manager( collide_manager ) {
	double y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT + FLOOR_HEIGHT / 2;
	ImagePtr test_texture = Drawer::getTask( )->getImage( TEST_TEXTURE );

	_spheres[ OBJECT_TAG_Q2SPHERE_1 ] = 
		Question2SpherePtr( new Question2Sphere( Vector( 0, y, 1000 ) * 0.001, test_texture, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, OBJECT_TAG_Q2SPHERE_1 ) );

	_spheres[ OBJECT_TAG_Q2SPHERE_2 ] =
		Question2SpherePtr( new Question2Sphere( Vector( 1000, y, 0 ) * 0.001, test_texture, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, OBJECT_TAG_Q2SPHERE_2 ) );

	_spheres[ OBJECT_TAG_Q2SPHERE_3 ] = 
		Question2SpherePtr( new Question2Sphere( Vector( 1000, y, 1000 ) * 0.001, test_texture, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, OBJECT_TAG_Q2SPHERE_3 ) );


	std::map< OBJECT_TAG, Question2SpherePtr >::iterator ite = _spheres.begin( );
	for ( ite; ite != _spheres.end( ); ite++ ) {
		_collide_manager->addDynamicCollider( ite->second );
	}
}

Question2FloorHint::~Question2FloorHint( ) {
}

void Question2FloorHint::drawQuestion2Hint( ) const {
	std::map< OBJECT_TAG, Question2SpherePtr >::const_iterator ite = _spheres.begin( );
	for ( ite; ite != _spheres.end( ); ite++ ) {
		ite->second->draw( );
	}
}

void Question2FloorHint::addDockingSphere( OBJECT_TAG tag ) {
	_docking_sphere.push_back( tag );
	if ( _docking_sphere.size( ) == 2 ) {
		dockingSphere( _docking_sphere[ 0 ], _docking_sphere[ 1 ] );
		_docking_sphere.clear( );
	}
}

void Question2FloorHint::dockingSphere( OBJECT_TAG tag1, OBJECT_TAG tag2 ) {
	if ( tag1 == OBJECT_TAG_Q2SPHERE_1 && tag2 == OBJECT_TAG_Q2SPHERE_2 ||
		 tag1 == OBJECT_TAG_Q2SPHERE_2 && tag2 == OBJECT_TAG_Q2SPHERE_1 ) {
		_spheres.erase( OBJECT_TAG_Q2SPHERE_1 );
		_spheres.erase( OBJECT_TAG_Q2SPHERE_2 );

		// debug
		double y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;
		ImagePtr test_texture = Drawer::getTask( )->getImage( TEST_TEXTURE );
		_spheres[ OBJECT_TAG_Q2SPHERE_4 ] = 
			Question2SpherePtr( new Question2Sphere( Vector( 1000, y, 2000 ) * 0.001, test_texture, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, OBJECT_TAG_Q2SPHERE_4 ) );
		_collide_manager->addDynamicCollider( _spheres.at( OBJECT_TAG_Q2SPHERE_4 ) );
	}

	if ( tag1 == OBJECT_TAG_Q2SPHERE_3 && tag2 == OBJECT_TAG_Q2SPHERE_4 ||
		 tag1 == OBJECT_TAG_Q2SPHERE_4 && tag2 == OBJECT_TAG_Q2SPHERE_3 ) {
		_spheres.erase( OBJECT_TAG_Q2SPHERE_3 );
		_spheres.erase( OBJECT_TAG_Q2SPHERE_4 );

		// debug
		double y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;
		ImagePtr test_texture = Drawer::getTask( )->getImage( TEST_TEXTURE );
		_spheres[ OBJECT_TAG_Q2SPHERE_5 ] = 
			Question2SpherePtr( new Question2Sphere( Vector( 1000, y, 2000 ) * 0.001, test_texture, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, OBJECT_TAG_Q2SPHERE_5 ) );
	}
}