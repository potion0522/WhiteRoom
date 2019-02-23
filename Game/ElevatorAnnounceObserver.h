#pragma once
#include "define.h"

class ElevatorAnnounceObserver {
public:
	virtual void announceArrive( FLOOR floor ) = 0;
	virtual void announceMove( ) = 0;
};

