#include "Floor3.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "QuestionManager.h"
#include "Question2FloorHint.h"
#include "Question4FloorHint.h"
#include "Question5FloorHint.h"
#include "DummySphere.h"

#include "Random.h"

Floor3::Floor3( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager ) :
MY_FLOOR( FLOOR_3 ),
Floor( collide_manager, observable, FLOOR_3 ) {

	{ // Question2
		_question2_hint = Question2FloorHintPtr( new Question2FloorHint( question_manager, collide_manager, MY_FLOOR ) );
		
		const int COLOR_IDX = question_manager->getHintQuestion2Color( MY_FLOOR );
		const int MAX_SPHERE = 4;
		const int MIN_SPHERE = 1;
		RandomPtr random = Random::getTask( );
		int num = random->getRand( MIN_SPHERE, MAX_SPHERE );
		for ( int i = 0; i < num; i++ ) {
			_dummy_spheres.push_back( DummySpherePtr( new DummySphere( collide_manager, MY_FLOOR, COLOR_IDX ) ) );
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
	for ( DummySpherePtr sphere : _dummy_spheres ) {
		sphere->update( );
	}
}

void Floor3::draw( ) const {
	
	drawFloor( );

	// question2
	_question2_hint->draw( );
	for ( DummySpherePtr sphere : _dummy_spheres ) {
		sphere->draw( );
	}

	// question4
	_question4_hint->draw( );

	// question5
	_question5_hint->draw( );
}
