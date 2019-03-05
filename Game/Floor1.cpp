#include "Floor1.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"

#include "Manager.h"

Floor1::Floor1( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor ) : 
Floor( collide_manager, observable, floor  ) {
}

Floor1::~Floor1( ) {
}

void Floor1::draw( ) const {
	drawFloor( );
}
