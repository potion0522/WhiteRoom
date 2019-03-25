#include "Floor5.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "Question5FloorHint.h"

Floor5::Floor5( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager ) :
MY_FLOOR( FLOOR_5 ),
Floor( collide_manager, observable, FLOOR_5 ) {
	_question5_hint = Question5FloorHintPtr( new Question5FloorHint( question_manager, MY_FLOOR ) );
}

Floor5::~Floor5( ) {
}

void Floor5::draw( ) const {
	drawFloor( );
	_question5_hint->draw( );
}
