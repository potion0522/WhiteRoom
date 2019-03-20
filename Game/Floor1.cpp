#include "Floor1.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "Question3FloorHint.h"

#include "Manager.h"

Floor1::Floor1( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager ) : 
MY_FLOOR( FLOOR_1 ),
Floor( collide_manager, observable, FLOOR_1 ) {
	_question3_hint = Question3FloorHintPtr( new Question3FloorHint( question_manager, MY_FLOOR ) );
}

Floor1::~Floor1( ) {
}

void Floor1::draw( ) const {
	drawFloor( );
	_question3_hint->draw( );
}
