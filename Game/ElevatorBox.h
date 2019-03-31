#pragma once
#include <functional>
#include <memory>
#include "Mathematics.h"

/********************************************

現実世界でいうエレベーターの部屋
乗っているだけで移動依頼とかは出来ない

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

