#pragma once
#include <functional>

class ConsoleActiveObserver {
public:
	virtual void onActive( bool active ) = 0;
};
