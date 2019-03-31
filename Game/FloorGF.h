#pragma once
#include "Floor.h"
/*******************************************************************

	Floorの描画などを担当するFloorクラスを継承したクラス
	FloorGF用のクラス

*******************************************************************/

PTR( FloorGF );

class FloorGF : public Floor {
public:
	FloorGF( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable );
	virtual ~FloorGF( );
};

