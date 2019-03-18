#include "Floor1.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "Question3FloorHint.h"

#include "Manager.h"

Floor1::Floor1( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor ) : 
Floor( collide_manager, observable, floor  ) {
	_question3_hint = Question3FloorHintPtr( new Question3FloorHint( question_manager, FLOOR_1 ) );
}

Floor1::~Floor1( ) {
}

void Floor1::draw( ) const {
	drawFloor( );
	_question3_hint->draw( );
}
