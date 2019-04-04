#include "UIActiveObserver.h"

UIActiveObserver::UIActiveObserver( ) {
}

UIActiveObserver::~UIActiveObserver( ) {
}


void UIActiveObserver::subscribeOnActive( std::function< void( bool ) > func ) {
	_on_active.push_back( func );
}

void UIActiveObserver::onActive( bool active ) {
	for ( int i = 0; i < _on_active.size( ); i++ ) {
		_on_active[ i ]( active );
	}
}