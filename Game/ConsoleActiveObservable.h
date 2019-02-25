#pragma once
#include <functional>

class ConsoleActiveObservable {
public:
	virtual void subscribeOnActive( std::function< void( bool ) > ) = 0;
};