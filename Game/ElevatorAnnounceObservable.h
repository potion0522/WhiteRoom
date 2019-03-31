#pragma once
#include <functional>
#include "define.h"

/**************************************************

�G���x�[�^�[�̒ʒm���󂯎�邽�߂̃C���^�[�t�F�[�X

***************************************************/

class ElevatorAnnounceObservable {
public:
	virtual void subscribeAnnounceArrive( std::function< void( FLOOR ) > func ) = 0;
	virtual void subscribeAnnounceMove( std::function< void( ) > func ) = 0;
};