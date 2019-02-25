#include "ConsoleObserver.h"

ConsoleObserver::ConsoleObserver( ) {
}

ConsoleObserver::~ConsoleObserver( ) {
}


void ConsoleObserver::subscribeOnActive( std::function< void( bool ) > func ) {
	_on_active.push_back( func );
}

void ConsoleObserver::onActive( bool active ) {
	for ( int i = 0; i < _on_active.size( ); i++ ) {
		_on_active[ i ]( active );
	}
}