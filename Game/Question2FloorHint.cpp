#include "Question2FloorHint.h"
#include "QuestionManager.h"
#include "Question2Sphere.h"
#include "CollideManager.h"

#include "Random.h"
#include "Drawer.h"

const char* Q2_TEXTURE_PATH = "Game/Texture/Q2Mark";

Question2FloorHint::Question2FloorHint( QuestionManagerConstPtr question_manager, CollideManagerPtr collide_manager, FLOOR floor ) :
_question_manager( question_manager ),
_collide_manager( collide_manager ),
_floor( floor ) {
	
	const int GENERATE_RANGE = ( int )( FLOOR_WIDTH - SPHERE_OBJECT_RADIUS * 2 );
	const int SPHERE_NUM = 3;

	RandomPtr random = Random::getTask( );
	std::vector< Vector > rand_pos;
	for ( int i = 0; i < SPHERE_NUM; i++ ) {
		Vector pos = Vector( );
		pos.x = ( -GENERATE_RANGE / 2 ) + ( random->getRand( ) % GENERATE_RANGE );
		pos.z = i * GENERATE_RANGE / SPHERE_NUM;
		pos.y = FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * _floor * -1 + SPHERE_OBJECT_RADIUS;
		rand_pos.push_back( pos );
	}

	_sphere_color_idx = question_manager->getHintQuestion2Color( _floor );
	generateSphere( OBJECT_TAG_Q2SPHERE_1, rand_pos[ 0 ] );
	generateSphere( OBJECT_TAG_Q2SPHERE_2, rand_pos[ 1 ] );
	generateSphere( OBJECT_TAG_Q2SPHERE_3, rand_pos[ 2 ] );
														 

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
	// 1’iŠK–Ú
	if ( tag1 == OBJECT_TAG_Q2SPHERE_1 && tag2 == OBJECT_TAG_Q2SPHERE_2 ||
		 tag1 == OBJECT_TAG_Q2SPHERE_2 && tag2 == OBJECT_TAG_Q2SPHERE_1 ) {

		// ¶¬
		Vector pos = _spheres[ OBJECT_TAG_Q2SPHERE_1 ]->getPos( );
		pos.y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT + SPHERE_OBJECT_RADIUS;

		generateSphere( OBJECT_TAG_Q2SPHERE_4, pos );
		_collide_manager->addDynamicCollider( _spheres.at( OBJECT_TAG_Q2SPHERE_4 ) );

		// íœ
		_spheres.erase( OBJECT_TAG_Q2SPHERE_1 );
		_spheres.erase( OBJECT_TAG_Q2SPHERE_2 );
		return;
	}

	// 2’iŠK–Ú
	if ( tag1 == OBJECT_TAG_Q2SPHERE_3 && tag2 == OBJECT_TAG_Q2SPHERE_4 ||
		 tag1 == OBJECT_TAG_Q2SPHERE_4 && tag2 == OBJECT_TAG_Q2SPHERE_3 ) {

		// ¶¬
		Vector pos = _spheres[ OBJECT_TAG_Q2SPHERE_3 ]->getPos( );
		pos.y = ( int )_floor * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT + SPHERE_OBJECT_RADIUS;

		generateSphere( OBJECT_TAG_Q2SPHERE_5, pos );
		_collide_manager->addDynamicCollider( _spheres.at( OBJECT_TAG_Q2SPHERE_5 ) );

		// íœ
		_spheres.erase( OBJECT_TAG_Q2SPHERE_3 );
		_spheres.erase( OBJECT_TAG_Q2SPHERE_4 );
		return;
	}
}

void Question2FloorHint::generateSphere( OBJECT_TAG tag, const Vector& pos ) {
	int mark_idx = _question_manager->getHintQuestion2Mark( _floor );
	int div_idx  = tag - OBJECT_TAG_Q2SPHERE_1;

	std::string path = Q2_TEXTURE_PATH;
	path += std::to_string( mark_idx );
	path += "_";
	path += std::to_string( div_idx );
	path += ".png";


	DrawerPtr drawer = Drawer::getTask( );
	ImagePtr image = drawer->getImage( path.c_str( ) );

	_spheres[ tag ] = Question2SpherePtr( new Question2Sphere( pos, image, _sphere_color_idx, [ & ]( OBJECT_TAG tag ) { addDockingSphere( tag ); }, tag ) );
}