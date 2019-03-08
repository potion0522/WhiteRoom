#include "Floor2.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "Question1FloorHint.h"
#include "Question2FloorHint.h"

#include "Manager.h"

Floor2::Floor2( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor ) : 
Floor( collide_manager, observable, floor  ) {
	_question1_hint = Question1FloorHintPtr( new Question1FloorHint( question_manager ) );
	_question2_hint = Question2FloorHintPtr( new Question2FloorHint( question_manager, collide_manager, FLOOR_2 ) );
}

Floor2::~Floor2( ) {
}

void Floor2::draw( ) const {

	drawFloor( );

	// question1
	Manager* manager = Manager::getInstance( );
	manager->setWriteZBaffur( false );
	_question1_hint->drawQuestion1Hint( );
	manager->setWriteZBaffur( true );

	// question2
	_question2_hint->drawQuestion2Hint( );
}
