#pragma once
#include <functional>
#include "define.h"

class ElevatorButton {
public:
	ElevatorButton( std::function< void( FLOOR ) > func );
	virtual ~ElevatorButton( );

public:
	void pushButton( FLOOR floor );

private:
	std::function< void( FLOOR ) > _button;
};

