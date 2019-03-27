#include "ConsoleQuestion.h"
#include "SoundManager.h"

#include "Manager.h"

ConsoleQuestion::ConsoleQuestion( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
PageContent( callback ),
_question_manager( question_manager ),
_state( STATE_NONE ),
_start_time( 0 ) {
}

ConsoleQuestion::~ConsoleQuestion( ) {
}

void ConsoleQuestion::update( ) {
	switch ( _state ) {
		case STATE_NONE:
			actOnNone( );
			break;

		case STATE_PUSH:
			actOnPush( );
			break;

		case STATE_PUSH_UP:
			actOnPushUp( );
			break;

		case STATE_ANSWER:
			actOnAnswer( );
			break;
	}
}

void ConsoleQuestion::refresh( ) {
	// “š‚¦‡‚í‚¹‚È‚çƒŠƒtƒŒƒbƒVƒ…‚µ‚È‚¢
	if ( _state == STATE_ANSWER ) {
		return;
	}
	_state = STATE_NONE;
}

int ConsoleQuestion::getNowCount( ) const {
	return Manager::getInstance( )->getNowCount( );
}

void ConsoleQuestion::playClearSE( ) {
	SoundManager::getInstance( )->play( SoundManager::SE_QUESTION_CLEAR );
}

void ConsoleQuestion::playUnClearSE( ) {
	SoundManager::getInstance( )->play( SoundManager::SE_QUESTION_UNCLEAR );
}