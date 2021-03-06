#pragma once
#include "ElevatorAnnounceObservable.h"
#include "ElevatorAnnounceObserver.h"
#include <vector>

/*************************************************

エレベーターの到着、移動のアナウンスを通知するクラス
UnityでいうUniRxの構造を参考にしている

*************************************************/

class ElevatorAnnounce : public ElevatorAnnounceObservable, public ElevatorAnnounceObserver {
public:
	ElevatorAnnounce( );
	virtual ~ElevatorAnnounce( );

public:
	void subscribeAnnounceArrive( std::function< void( FLOOR floor ) > func );
	void subscribeAnnounceMove( std::function< void( ) > func );
	void announceArrive( FLOOR floor );
	void announceMove( );

private:
	std::vector< std::function< void( FLOOR floor ) > > _announce_arrive;
	std::vector< std::function< void( ) > > _announce_move;
};

