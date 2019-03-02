#pragma once
#include <functional>
#include "define.h"

/*

現実世界でいうエレベーターのボタン
移動の依頼しかできない

*/

class ElevatorButton {
public:
	ElevatorButton( std::function< void( FLOOR ) > func );
	virtual ~ElevatorButton( );

public:
	void pushButton( FLOOR floor );

private:
	std::function< void( FLOOR ) > _button;
};

