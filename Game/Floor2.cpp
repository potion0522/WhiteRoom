#include "Floor2.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"
#include "Question1FloorHint.h"

#include "Manager.h"

Floor2::Floor2( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor ) : 
Floor( collide_manager, observable, floor  ) {
	_question1_hint = Question1FloorHintPtr( new Question1FloorHint( question_manager ) );
}

Floor2::~Floor2( ) {
}

void Floor2::draw( ) const {

	drawFloor( );

	Manager* manager = Manager::getInstance( );
	manager->setWriteZBaffur( false );
	_question1_hint->drawQuestion1Hint( );
	manager->setWriteZBaffur( true );
}
