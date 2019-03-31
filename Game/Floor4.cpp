#include "Floor4.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "QuestionManager.h"
#include "Question2FloorHint.h"
#include "Question3FloorHint.h"
#include "Question5FloorHint.h"
#include "Sphere.h"

#include "Random.h"

Floor4::Floor4( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager ) :
MY_FLOOR( FLOOR_4 ),
Floor( collide_manager, observable, FLOOR_4 ) {

	{ // Question2
		_question2_hint = Question2FloorHintPtr( new Question2FloorHint( question_manager, collide_manager, MY_FLOOR ) );
		
		const int COLOR_IDX = question_manager->getHintQuestion2Color( MY_FLOOR );
		const int MAX_SPHERE = 4;
		const int MIN_SPHERE = 1;
		// �����͈�
		const int GENERATE_RANGE = ( int )( FLOOR_WIDTH - SPHERE_OBJECT_RADIUS * 2 );

		RandomPtr random = Random::getTask( );
		int num = random->getRand( MIN_SPHERE, MAX_SPHERE );
		for ( int i = 0; i < num; i++ ) {
			Vector pos = Vector( );
			pos.x = -FLOOR_WIDTH / 2 + SPHERE_OBJECT_RADIUS + random->getRand( 0, GENERATE_RANGE );
			pos.z = -FLOOR_WIDTH / 2 + SPHERE_OBJECT_RADIUS + random->getRand( 0, GENERATE_RANGE );
			pos.y = FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * MY_FLOOR * -1 + SPHERE_OBJECT_RADIUS;
			_dummy_spheres.push_back( SpherePtr( new Sphere( pos, SPHERE_OBJECT_RADIUS, COLOR_IDX ) ) );
			collide_manager->addDynamicCollider( _dummy_spheres[ i ] );
		}
	}

	// Question3
	_question3_hint = Question3FloorHintPtr( new Question3FloorHint( question_manager, MY_FLOOR ) );

	// Question5
	_question5_hint = Question5FloorHintPtr( new Question5FloorHint( question_manager, MY_FLOOR ) );
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

	// question3
	_question3_hint->draw( );

	// question5
	_question5_hint->draw( );
}
