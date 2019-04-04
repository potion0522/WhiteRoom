#include "UI.h"
#include "UICanvas.h"
#include "Console.h"
#include "Hint.h"
#include "UIActiveObserver.h"
#include "SoundManager.h"

#include "Keyboard.h"
#include "Mouse.h"

UI::UI( ElevatorButtonPtr elevator_button, QuestionManagerPtr question_manager ) :
_state( UI_STATE_CLOSE ),
_active_key( ) {
	_observer = UIActiveObserverPtr( new UIActiveObserver );
	_console = ConsolePtr( new Console( elevator_button, question_manager ) );
	_hint    = HintPtr( new Hint( question_manager ) );
}

UI::~UI( ) {
}

void UI::update( ) {
	switch ( _state ) {
	case UI_STATE_CLOSE:
		actOnClose( );
		break;

	case UI_STATE_OPEN:
		actOnOpen( );
		break;
	}
}

void UI::draw( ) const {
	UICanvasPtr canvas = _canvas.lock( );
	if ( canvas ) {
		canvas->draw( );
	}
}

UIActiveObservableComponentPtr UI::getActiveObservable( ) const {
	return _observer;
}

void UI::actOnClose( ) {

	// console
	if ( isKeyDown( CONSOLE_ACTIVE_KEY ) ) {
		_canvas = _console;
		_active_key = CONSOLE_ACTIVE_KEY;
	}
	// hint
	else if ( isKeyDown( HINT_ACTIVE_KEY ) ) {
		_canvas = _hint;
		_active_key = HINT_ACTIVE_KEY;
	}

	UICanvasPtr canvas = _canvas.lock( );
	if ( canvas ) {
		_state = UI_STATE_OPEN;
		_observer->onActive( true );
		canvas->open( );

		MousePtr mouse = Mouse::getTask( );
		mouse->setMouseDraw( true );
		SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_OPEN );
	}
}

void UI::actOnOpen( ) {
	UICanvasPtr canvas = _canvas.lock( );
	if ( canvas ) {
		canvas->update( );
	}

	// I—¹ˆ—
	if ( isKeyDown( _active_key ) ) {
		_state = UI_STATE_CLOSE;
		canvas->close( );
		_observer->onActive( false );

		_canvas = UICanvasPtr( );

		MousePtr mouse = Mouse::getTask( );
		mouse->setMouseDraw( false );
		SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_CLOSE );
	}
}

bool UI::isKeyDown( const std::string& key ) const {
	return Keyboard::getTask( )->getKeyDown( key );
}