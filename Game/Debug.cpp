#include "Debug.h"
#include "Manager.h"

Debug* Debug::_instance;

#ifdef DEBUG
#include "define.h"

#include "Drawer.h"
#include <vector>

class Impl {
private:
	const float SAVE_MESSAGE_X = 20;
	const float NON_SAVE_MESSAGE_X = SCREEN_WIDTH - SCREEN_WIDTH / 3;

public:

	void update( ) {
		DrawerPtr drawer = Drawer::getTask( );
		// 保存したメッセージ
		for ( int i = 0; i < _save_message.size( ); i++ ) {
			drawer->drawString( SAVE_MESSAGE_X, i * 20.0f, _save_message[ i ].c_str( ), 0xff0000 );
		}

		// 毎フレーム更新するメッセージ
		for ( int i = 0; i < _message.size( ); i++ ) {
			drawer->drawString( NON_SAVE_MESSAGE_X, i * 20.0f, _message[ i ].c_str( ), 0xff0000 );
		}
		_message.clear( );
	}
	void clearSaveMessage( ) {
		_save_message.clear( );
	}
	void addSaveMessage( const char* message ) {
		_save_message.push_back( message );
	}
	void addMessage( const char* message ) {
		_message.push_back( message );
	}

private:
	std::vector< std::string > _save_message;
	std::vector< std::string > _message;
};

#else
class Impl {
public:
	void update( ) { }
	void clearSaveMessage( ) { }
	void addSaveMessage( const char* message ) { }
	void addMessage( const char* message ) { }
};

#endif


Debug::Debug( ) {
	_impl = ImplPtr( new Impl );
}

Debug::~Debug( ) {
}

Debug* Debug::getInstance( ) {
	if ( !_instance ) {
		_instance = new Debug;
	}
	return _instance;
}

void Debug::finalize( ) {
	if ( _instance ) {
		delete _instance;
	}
}

void Debug::update( ) {
	_impl->update( );
}

void Debug::clearSaveMessage( ) {
	_impl->clearSaveMessage( );
}

void Debug::addSaveMessage( const char* message ) {
	_impl->addSaveMessage( message );
}

void Debug::addMessage( const char* message ) {
	_impl->addMessage( message );
}