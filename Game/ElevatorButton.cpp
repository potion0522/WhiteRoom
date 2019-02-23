#include "ElevatorButton.h"

ElevatorButton::ElevatorButton( std::function< void( FLOOR ) > func ) :
_button( func ) {
}

ElevatorButton::~ElevatorButton( ) {
}

void ElevatorButton::pushButton( FLOOR floor ) {
	_button( floor );
}