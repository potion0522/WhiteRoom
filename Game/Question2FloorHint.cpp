#include "Question2FloorHint.h"
#include "QuestionManager.h"
#include "Question2Sphere.h"
#include "CollideManager.h"

#include "Drawer.h"

const char* TEST_TEXTURE = "Game/Texture/ElevatorTexture.png";
const char* TEXTURE[ 3 ][ 5 ] = {
	{ "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png" },
	{ "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png" },
	{ "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png", "Game/Texture/ClubTexture.png" },
};

Question2FloorHint::Question2FloorHint( QuestionManagerConstPtr question_manager, CollideManagerPtr collide_manager, FLOOR floor ) :
_floor( floor ),
_collide_manager( collide_manager ) {
	double y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;
	ImagePtr test_texture = Drawer::getTask( )->getImage( TEST_TEXTURE );

	generateSphere( OBJECT_TAG_Q2SPHERE_1, Vector(    0, y, 1000 ) );
	generateSphere( OBJECT_TAG_Q2SPHERE_2, Vector( 1000, y,    0 ) );
	generateSphere( OBJECT_TAG_Q2SPHERE_3, Vector( 1000, y, 1000 ) );


	std::map< OBJECT_TAG, Question2SpherePtr >::iterator ite = _spheres.begin( );
	for ( ite; ite != _spheres.end( ); ite++ ) {
		_collide_manager->addDynamicCollider( ite->second );
	}
}

Question2FloorHint::~Question2FloorHint( ) {
}

void Question2FloorHint::update( ) {
	for ( const std::pair< OBJECT_TAG, Question2SpherePtr >& sphere : _spheres ) {
		sphere.second->update( );
	}
}

void Question2FloorHint::draw( ) const {
	for ( const std::pair< OBJECT_TAG, Question2SpherePtr >& sphere : _spheres ) {
		sphere.second->draw( );
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
	//if ( tag1 == OBJECT_TAG_Q2SPHERE_1 && tag2 == OBJECT_TAG_Q2SPHERE_2 ||
	//	 tag1 == OBJECT_TAG_Q2SPHERE_2 && tag2 == OBJECT_TAG_Q2SPHERE_1 ) {
	//	_spheres.erase( OBJECT_TAG_Q2SPHERE_1 );
	//	_spheres.erase( OBJECT_TAG_Q2SPHERE_2 );

	//	// debug
	//	double y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;
	//	ImagePtr test_texture = Drawer::getTask( )->getImage( TEST_TEXTURE );
	//	_spheres[ OBJECT_TAG_Q2SPHERE_4 ] = 
	//		Question2SpherePtr( new Question2Sphere( Vector( 1000, y, 2000 ) * 0.001, test_texture, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, OBJECT_TAG_Q2SPHERE_4 ) );
	//	_collide_manager->addDynamicCollider( _spheres.at( OBJECT_TAG_Q2SPHERE_4 ) );
	//}

	//if ( tag1 == OBJECT_TAG_Q2SPHERE_3 && tag2 == OBJECT_TAG_Q2SPHERE_4 ||
	//	 tag1 == OBJECT_TAG_Q2SPHERE_4 && tag2 == OBJECT_TAG_Q2SPHERE_3 ) {
	//	_spheres.erase( OBJECT_TAG_Q2SPHERE_3 );
	//	_spheres.erase( OBJECT_TAG_Q2SPHERE_4 );

	//	// debug
	//	double y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;
	//	ImagePtr test_texture = Drawer::getTask( )->getImage( TEST_TEXTURE );
	//	_spheres[ OBJECT_TAG_Q2SPHERE_5 ] = 
	//		Question2SpherePtr( new Question2Sphere( Vector( 1000, y, 2000 ) * 0.001, test_texture, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, OBJECT_TAG_Q2SPHERE_5 ) );
	//}
}

void Question2FloorHint::generateSphere( OBJECT_TAG tag, const Vector& pos ) {
	int texture_idx_row = _floor - FLOOR_2;
	int texture_idx_col = tag - OBJECT_TAG_Q2SPHERE_1;
	DrawerPtr drawer = Drawer::getTask( );
	ImagePtr image = drawer->getImage( TEXTURE[ texture_idx_row ][ texture_idx_col ] );

	_spheres[ tag ] = Question2SpherePtr( new Question2Sphere( pos, image, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, tag ) );
}