#pragma once
#include <functional>
#include <memory>
#include "Mathematics.h"

/********************************************

�������E�ł����G���x�[�^�[�̕���
����Ă��邾���ňړ��˗��Ƃ��͏o���Ȃ�

********************************************/

class ElevatorBox {
public:
	ElevatorBox( std::function< void( Vector* ) > func );
	virtual ~ElevatorBox( );

public:
	void requestRideOnElevator( Vector* obj_pos );

private:
	std::function< void( Vector* ) > _ride_on;
};

