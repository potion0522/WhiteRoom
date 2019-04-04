#include "UI.h"
#include "UICanvas.h"
#include "Console.h"
#include "Hint.h"
#include "UIActiveObserver.h"
#include "SoundManager.h"
#include "QuestionManager.h"

#include "Manager.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Mouse.h"

UI::UI( ElevatorButtonPtr elevator_button, QuestionManagerPtr question_manager ) :
_idle_time( 0 ),
_ui_text_alpha( 0 ),
_state( UI_STATE_CLOSE ),
_active_key( ),
_question_manager( question_manager ) {
	_observer = UIActiveObserverPtr( new UIActiveObserver );
	_console = ConsolePtr( new Console( elevator_button, question_manager ) );
	_hint    = HintPtr( new Hint( question_manager ) );
	_past_time = Manager::getInstance( )->getNowCount( );
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
	switch ( _state ) {
	case UI_STATE_CLOSE:
		drawOnClose( );
		break;

	case UI_STATE_OPEN:
		drawOnOpen( );
		break;
	}
}

UIActiveObservableComponentPtr UI::getActiveObservable( ) const {
	return _observer;
}

void UI::actOnClose( ) {
	updateIdleTime( );
	checkOpen( );
}

void UI::actOnOpen( ) {
	UICanvasPtr canvas = _canvas.lock( );
	if ( canvas ) {
		canvas->update( );
	}

	// I—¹ˆ—
	if ( isKeyDown( _active_key ) ) {
		changeState( UI_STATE_CLOSE );
		canvas->close( );
		_observer->onActive( false );

		_canvas = UICanvasPtr( );

		MousePtr mouse = Mouse::getTask( );
		mouse->setMouseDraw( false );
		SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_CLOSE );
	}
}

void UI::drawOnClose( ) const {
	const int FONT_SIZE = 30;
	const int COLOR = 0x000000; // •
	const int MAX_ALPHA = 255;

	DrawerPtr drawer = Drawer::getTask( );
	drawer->setAlpha( _ui_text_alpha );
	// ‘€ìƒqƒ“ƒg
	const float KEY_HINT_X = FONT_SIZE / 2.0f;
	drawer->drawFormatString( KEY_HINT_X, FONT_SIZE / 2.0f, COLOR, FONT_SIZE, "%s : ƒRƒ“ƒ\[ƒ‹", CONSOLE_ACTIVE_KEY );
	drawer->drawFormatString( KEY_HINT_X, FONT_SIZE / 2.0f + FONT_SIZE, COLOR, FONT_SIZE, "%s : ƒqƒ“ƒg", HINT_ACTIVE_KEY );

	// ’Eo—¦
	std::string str = "’Eo—¦ : ";
	str += std::to_string( _question_manager->getQuestionAnswerRate( ) ) + "%";
	const float ESCAPE_RATE_X = SCREEN_WIDTH - ( float )drawer->getStringWidth( str.c_str( ), FONT_SIZE ) - FONT_SIZE * 2; // 2•¶Žš•ª‰E‚É—]”’
	drawer->drawFormatString( ESCAPE_RATE_X, FONT_SIZE / 2.0f + FONT_SIZE, COLOR, FONT_SIZE, "%s", str.c_str( ) );
	drawer->setAlpha( MAX_ALPHA );
}

void UI::drawOnOpen( ) const {
	UICanvasPtr canvas = _canvas.lock( );
	if ( canvas ) {
		canvas->draw( );
	}

	DrawerPtr drawer = Drawer::getTask( );
	const int FONT_SIZE = 30;
	const int COLOR = 0x000000; // •
	drawer->drawFormatString( FONT_SIZE / 2.0f, FONT_SIZE / 2.0f, COLOR, FONT_SIZE, "%s : •Â‚¶‚é", _active_key.c_str( ) );
}

void UI::updateIdleTime( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	// ÃŽ~‚µ‚Ä‚¢‚éŽžŠÔ“ü—Í
	if ( keyboard->getString( ).empty( ) ) {
		int now = Manager::getInstance( )->getNowCount( );
		int delta_time = now - _past_time;
		_idle_time += delta_time;
		_past_time = now;
	} else {
		_idle_time = 0;
	}

	const int MAX_IDLE_TIME = SHOW_UI_TEXT_START_TIME + SHOW_UI_TEXT_ANIM_TIME;
	if ( _idle_time > MAX_IDLE_TIME ) {
		_idle_time = MAX_IDLE_TIME;
	}

	// alpha ‚ÌŒvŽZ
	const int MAX_ALPHA = 255;
	if ( _idle_time < SHOW_UI_TEXT_START_TIME ) {
		_ui_text_alpha = ( int )( _ui_text_alpha * 0.8 );
	} else {
		double ratio = ( _idle_time - SHOW_UI_TEXT_START_TIME ) / ( double )SHOW_UI_TEXT_ANIM_TIME;
		_ui_text_alpha = ( int )( MAX_ALPHA * ratio );
	}
}

void UI::checkOpen( ) {
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
		changeState( UI_STATE_OPEN );
		_observer->onActive( true );
		canvas->open( );

		MousePtr mouse = Mouse::getTask( );
		mouse->setMouseDraw( true );
		SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_OPEN );
	}
}

void UI::changeState( UI_STATE state ) {
	_state = state;
	_idle_time = 0;
	_ui_text_alpha = 0;
	_past_time = Manager::getInstance( )->getNowCount( );
}

bool UI::isKeyDown( const std::string& key ) const {
	return Keyboard::getTask( )->getKeyDown( key );
}