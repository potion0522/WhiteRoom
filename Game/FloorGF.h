#pragma once
#include "Floor.h"

PTR( FloorGF );

class FloorGF : public Floor {
public:
	FloorGF( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable );
	virtual ~FloorGF( );
};

