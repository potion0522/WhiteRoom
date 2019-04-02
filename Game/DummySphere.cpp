#include "DummySphere.h"
#include "CollideManager.h"

#include "Random.h"

DummySphere::DummySphere( CollideManagerPtr collide_manager, FLOOR floor, int color_idx ) {
	// ¶¬”ÍˆÍ
	const int GENERATE_RANGE = ( int )( FLOOR_WIDTH - SPHERE_OBJECT_RADIUS * 2 );

	RandomPtr random = Random::getTask( );
	Vector pos = Vector( );
	pos.x = -FLOOR_WIDTH / 2 + SPHERE_OBJECT_RADIUS + random->getRand( 0, GENERATE_RANGE );
	pos.z = -FLOOR_WIDTH / 2 + SPHERE_OBJECT_RADIUS + random->getRand( 0, GENERATE_RANGE );
	pos.y = FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * floor * -1 + SPHERE_OBJECT_RADIUS;
	_sphere = SpherePtr( new Sphere( pos, SPHERE_OBJECT_RADIUS, color_idx ) );
	collide_manager->addDynamicCollider( _sphere );
}

DummySphere::~DummySphere( ) {
}

void DummySphere::update( ) {
	_sphere->update( );
}

void DummySphere::draw( ) const {
	_sphere->draw( );
}
