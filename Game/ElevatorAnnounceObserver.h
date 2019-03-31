#pragma once
#include "define.h"

/**************************************************

エレベーターの通知を発行するためのインターフェース

***************************************************/

class ElevatorAnnounceObserver {
public:
	virtual void announceArrive( FLOOR floor ) = 0;
	virtual void announceMove( ) = 0;
};

