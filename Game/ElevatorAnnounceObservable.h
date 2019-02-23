#pragma once
#include <functional>
#include "define.h"

class ElevatorAnnounceObservable {
public:
	virtual void subscribeAnnounceArrive( std::function< void( FLOOR ) > func ) = 0;
	virtual void subscribeAnnounceMove( std::function< void( ) > func ) = 0;
};