#pragma once
#include "define.h"

/**************************************************

�G���x�[�^�[�̒ʒm�𔭍s���邽�߂̃C���^�[�t�F�[�X

***************************************************/

class ElevatorAnnounceObserver {
public:
	virtual void announceArrive( FLOOR floor ) = 0;
	virtual void announceMove( ) = 0;
};

