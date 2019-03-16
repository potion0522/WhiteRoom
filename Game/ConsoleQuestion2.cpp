#include "ConsoleQuestion2.h"
#include "QuestionManager.h"

#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"

// 1.club 2.heart 3.diamont 4.spade
const char* IMAGE_FILE = "Game/Console/Question/Suits.png";

const int SUIT_SIZE = 256;
const int SPACE = ( SCREEN_WIDTH - SUIT_SIZE * 2 ) / QuestionManager::QUESTION_2_MAX_SUIT_NUM;

ConsoleQuestion2::ConsoleQuestion2( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ),
_state( STATE_NONE ) {
	DrawerPtr drawer = Drawer::getTask( );
	_suits = drawer->getImage( IMAGE_FILE );
	_suits->setCentral( true );

	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		_suits_state[ i ] = QuestionManager::SUIT_SPADE;
	}
}

ConsoleQuestion2::~ConsoleQuestion2( ) {
}

void ConsoleQuestion2::update( ) {
	switch ( _state ) {
		case STATE_NONE:
			break;

		case STATE_PUSH:
			break;

		case STATE_PUSH_UP:
			break;
	}
}


void ConsoleQuestion2::draw( int x, int y ) const {
	// 円
	const int CIRCLE_COLOR = 0xaaaaaa;
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		float draw_x = ( SPACE + SUIT_SIZE / 2 ) + i * SUIT_SIZE / 2 + i * SPACE;
		float draw_y = SCREEN_HEIGHT / 2;
		float radius = SUIT_SIZE * 0.8f;

		drawer->drawCircle( draw_x + x, draw_y + y, radius, CIRCLE_COLOR, true );
	}

	// マーク
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		int draw_x = ( SPACE + SUIT_SIZE / 2 ) + i * SUIT_SIZE / 2 + i * SPACE;
		int draw_y = SCREEN_HEIGHT / 2;

		// rect
		int rect_x = _suits_state[ i ] * SUIT_SIZE;
		int rect_y = 0;
		int width  = SUIT_SIZE;
		int height = SUIT_SIZE;

		_suits->setPos( draw_x + x, draw_y + y );
		_suits->setRect( 0, 0, width, height );

		_suits->draw( );
	}
}

void ConsoleQuestion2::actOnNone( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isClickDownLeft( ) ) {
		Vector pos = mouse->getPoint( );
	}
}

void ConsoleQuestion2::actOnPush( ) {
}

void ConsoleQuestion2::actOnPushUp( ) {
}
