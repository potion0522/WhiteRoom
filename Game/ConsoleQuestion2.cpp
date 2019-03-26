#include "ConsoleQuestion2.h"
#include "QuestionManager.h"

#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"

// 1.club 2.heart 3.diamont 4.spade
const char* IMAGE_FILE = "Game/Console/suits.png";

const int SUIT_SIZE = 256;
const int SPACE = ( SCREEN_WIDTH - SUIT_SIZE * 2 ) / QuestionManager::QUESTION_2_MAX_MARK_NUM;
const float CIRCLE_RADIUS = SUIT_SIZE * 0.8f; 

ConsoleQuestion2::ConsoleQuestion2( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ) {
	DrawerPtr drawer = Drawer::getTask( );
	_mark_image = drawer->getImage( IMAGE_FILE );
	_mark_image->setCentral( true );

	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		_mark_state[ i ] = 0;
	}
}

ConsoleQuestion2::~ConsoleQuestion2( ) {
}

void ConsoleQuestion2::draw( int x, int y ) const {
	// 円
	const int CIRCLE_COLOR = 0xaaaaaa;
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		float draw_x = ( SPACE + SUIT_SIZE / 2.0f ) + i * SUIT_SIZE / 2.0f + i * SPACE;
		float draw_y = SCREEN_HEIGHT / 2;

		drawer->drawCircle( draw_x + x, draw_y + y, CIRCLE_RADIUS, CIRCLE_COLOR, true );
	}

	// マーク
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		int draw_x = ( SPACE + SUIT_SIZE / 2 ) + i * SUIT_SIZE / 2 + i * SPACE;
		int draw_y = SCREEN_HEIGHT / 2;

		// rect
		int rect_x = _mark_state[ i ] * SUIT_SIZE;
		int rect_y = 0;
		int width  = SUIT_SIZE;
		int height = SUIT_SIZE;

		_mark_image->setPos( draw_x + x, draw_y + y );
		_mark_image->setRect( rect_x, rect_y, width, height );

		_mark_image->draw( );
	}
}

void ConsoleQuestion2::actOnNone( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isClickDownLeft( ) ) {
		if ( isMouseOnButton( ) ) {
			_state = STATE_PUSH;
		}
	}
}

void ConsoleQuestion2::actOnPush( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->getClickingLeft( ) < 1 ) {
		if ( isMouseOnButton( ) ) {
			_state = STATE_PUSH_UP;
		} else {
			_state = STATE_NONE;
		}
	}
}

void ConsoleQuestion2::actOnPushUp( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );
	
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		double circle_x = ( SPACE + SUIT_SIZE / 2.0 ) + i * SUIT_SIZE / 2.0 + i * SPACE;
		double circle_y = SCREEN_HEIGHT / 2;

		Vector circle_pos = Vector( circle_x, circle_y );
		if ( ( circle_pos - pos ).getLength2( ) < CIRCLE_RADIUS * CIRCLE_RADIUS ) {
			_mark_state[ i ] = ( _mark_state[ i ] + 1 ) % QuestionManager::QUESTION_2_MAX_MARK_NUM;
			break;
		}
	}
	// 音
	playClickSE( );


	_state = STATE_ANSWER;
	_start_time = getNowCount( );
}

void ConsoleQuestion2::actOnAnswer( ) {
	bool answer = _question_manager->answerQuestion2( _mark_state[ 0 ], _mark_state[ 1 ], _mark_state[ 2 ] );

	if ( answer ) {
		// クリア後一定時間待機
		if ( getNowCount( ) - _start_time > ANSWER_WAIT_TIME ) {
			playClearSE( );
			_callback( );
		}
	} else {
		_state = STATE_NONE;
	}
}

bool ConsoleQuestion2::isMouseOnButton( ) const {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );
	
	bool on_button = false;
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		double circle_x = ( SPACE + SUIT_SIZE / 2.0 ) + i * SUIT_SIZE / 2.0 + i * SPACE;
		double circle_y = SCREEN_HEIGHT / 2;

		Vector circle_pos = Vector( circle_x, circle_y );
		if ( ( circle_pos - pos ).getLength2( ) < CIRCLE_RADIUS * CIRCLE_RADIUS ) {
			on_button = true;
			break;
		}
	}

	return on_button;
}
