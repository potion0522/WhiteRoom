#include "Floor4.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "QuestionManager.h"
#include "Question2FloorHint.h"
#include "Question3FloorHint.h"
#include "Question5FloorHint.h"
#include "DummySphere.h"
#include "Q2DockingHint.h"

#include "Random.h"

Floor4::Floor4( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager ) :
MY_FLOOR( FLOOR_4 ),
Floor( collide_manager, observable, FLOOR_4 ) {

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

	// 球体のドッキングヒント
	Vector docking_hint_pos;
	docking_hint_pos.x = 0;
	docking_hint_pos.y = FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * MY_FLOOR * -1 + FLOOR_HEIGHT / 2;
	docking_hint_pos.z = -FLOOR_WIDTH / 2 + 20; // 20は壁とのスペース(適当)

	Matrix docking_hint_rot = Matrix::makeTransformRotation( Vector( 0, 1 ), PI );
	_q2_docking_hint = Q2DockingHintPtr( new Q2DockingHint( docking_hint_pos, docking_hint_rot ) );
}

Floor4::~Floor4( ) {
}

void Floor4::update( ) {
	_question2_hint->update( );
	for ( DummySpherePtr sphere : _dummy_spheres ) {
		sphere->update( );
	}
}

void Floor4::draw( ) const {

	drawFloor( );

	// question2
	_question2_hint->draw( );
	for ( DummySpherePtr sphere : _dummy_spheres ) {
		sphere->draw( );
	}

	// question3
	_question3_hint->draw( );

	// question5
	_question5_hint->draw( );

	_q2_docking_hint->draw( );
}
