#include "ElevatorBox.h"

ElevatorBox::ElevatorBox( std::function< void( Vector* ) > func ) :
_ride_on( func ) {
}

ElevatorBox::~ElevatorBox( ) {
}

void ElevatorBox::requestRideOnElevator( Vector* obj_pos ) {
	// �G���x�[�^�[�ɏ悹��
	_ride_on( obj_pos );
}