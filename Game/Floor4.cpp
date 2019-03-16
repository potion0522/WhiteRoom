#include "Floor4.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "Question1FloorHint.h"
#include "Question2FloorHint.h"
#include "Sphere.h"

#include "Manager.h"
#include "Random.h"

Floor4::Floor4( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor ) : 
Floor( collide_manager, observable, floor  ) {

	{ // Question2
		_question2_hint = Question2FloorHintPtr( new Question2FloorHint( question_manager, collide_manager, FLOOR_4 ) );

		const int MAX_SPHERE = 4;
		const int MIN_SPHERE = 1;
		// ¶¬”ÍˆÍ
		const int GENERATE_RANGE = ( int )( FLOOR_WIDTH - SPHERE_OBJECT_RADIUS * 2 );

		RandomPtr random = Random::getTask( );
		int num = random->getRand( MIN_SPHERE, MAX_SPHERE );
		for ( int i = 0; i < num; i++ ) {
			Vector pos = Vector( );
			pos.x = ( -GENERATE_RANGE / 2 ) + ( random->getRand( ) % GENERATE_RANGE );
			pos.z = ( -GENERATE_RANGE / 2 ) + ( random->getRand( ) % GENERATE_RANGE );
			pos.y = FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * FLOOR_4 * -1 + SPHERE_OBJECT_RADIUS;
			_dummy_spheres.push_back( SpherePtr( new Sphere( pos, SPHERE_OBJECT_RADIUS ) ) );
			collide_manager->addDynamicCollider( _dummy_spheres[ i ] );
		}
	}
}

Floor4::~Floor4( ) {
}

void Floor4::update( ) {
	_question2_hint->update( );
	for ( SpherePtr sphere : _dummy_spheres ) {
		sphere->update( );
	}
}

void Floor4::draw( ) const {

	drawFloor( );

	// question2
	_question2_hint->draw( );
	for ( SpherePtr sphere : _dummy_spheres ) {
		sphere->draw( );
	}
}
