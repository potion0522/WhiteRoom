#pragma once
#include "Floor.h"
/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	FloorGF�p�̃N���X

*******************************************************************/

PTR( FloorGF );

class FloorGF : public Floor {
public:
	FloorGF( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable );
	virtual ~FloorGF( );
};

