#include "Floor3.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "QuestionManager.h"
#include "Question2FloorHint.h"
#include "Question4FloorHint.h"
#include "Question5FloorHint.h"
#include "Sphere.h"

#include "Random.h"

Floor3::Floor3( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager ) :
MY_FLOOR( FLOOR_3 ),
Floor( collide_manager, observable, FLOOR_3 ) {

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
			pos.x = ( -GENERATE_RANGE / 2 ) + ( random->getRand( ) % GENERATE_RANGE );
			pos.z = ( -GENERATE_RANGE / 2 ) + ( random->getRand( ) % GENERATE_RANGE );
			pos.y = FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * MY_FLOOR * -1 + SPHERE_OBJECT_RADIUS;
			_dummy_spheres.push_back( SpherePtr( new Sphere( pos, SPHERE_OBJECT_RADIUS, COLOR_IDX ) ) );
			collide_manager->addDynamicCollider( _dummy_spheres[ i ] );
		}
	}

	// Question4
	_question4_hint = Question4FloorHintPtr( new Question4FloorHint( question_manager ) );

	// Question5
	_question5_hint = Question5FloorHintPtr( new Question5FloorHint( question_manager, MY_FLOOR ) );
}

Floor3::~Floor3( ) {
}

void Floor3::update( ) {
	_question2_hint->update( );
	for ( SpherePtr sphere : _dummy_spheres ) {
		sphere->update( );
	}
}

void Floor3::draw( ) const {

	drawFloor( );

	// question2
	_question2_hint->draw( );
	for ( SpherePtr sphere : _dummy_spheres ) {
		sphere->draw( );
	}

	// question4
	_question4_hint->draw( );

	// question5
	_question5_hint->draw( );
}
