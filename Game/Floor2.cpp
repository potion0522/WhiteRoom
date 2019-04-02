#include "Floor2.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "QuestionManager.h"
#include "Question1FloorHint.h"
#include "Question2FloorHint.h"
#include "Question3FloorHint.h"
#include "Question5FloorHint.h"
#include "ConsoleSlideHint.h"
#include "DummySphere.h"

#include "Random.h"

Floor2::Floor2( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager ) :
MY_FLOOR( FLOOR_2 ),
Floor( collide_manager, observable, FLOOR_2 ) {
	// Question1
	_question1_hint = Question1FloorHintPtr( new Question1FloorHint( question_manager ) );

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

	// Question3
	_question3_hint = Question3FloorHintPtr( new Question3FloorHint( question_manager, MY_FLOOR ) );

	// Question5
	_question5_hint = Question5FloorHintPtr( new Question5FloorHint( question_manager, MY_FLOOR ) );
	

	// コンソールのヒント
	Vector console_hint_pos;
	console_hint_pos.x = 0;
	console_hint_pos.y = FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * MY_FLOOR * -1 + FLOOR_HEIGHT / 2;
	console_hint_pos.z = -FLOOR_WIDTH / 2 + 20; // 20は壁とのスペース(適当)

	Matrix console_hint_rot = Matrix::makeTransformRotation( Vector( 0, 1 ), PI );
	_console_slide_hint = ConsoleSlideHintPtr( new ConsoleSlideHint( console_hint_pos, console_hint_rot ) );
}

Floor2::~Floor2( ) {
}

void Floor2::update( ) {
	_question2_hint->update( );
	for ( DummySpherePtr sphere : _dummy_spheres ) {
		sphere->update( );
	}
}

void Floor2::draw( ) const {

	drawFloor( );
	_console_slide_hint->draw( );

	// question1
	_question1_hint->draw( );

	// question2
	_question2_hint->draw( );
	for ( DummySpherePtr sphere : _dummy_spheres ) {
		sphere->draw( );
	}

	// question3
	_question3_hint->draw( );

	// question5
	_question5_hint->draw( );
}
