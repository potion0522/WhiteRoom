#include "ConsoleQuestion5.h"
#include "QuestionManager.h"

#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"

const char* ORDER_ARROW_IMAGE = "Game/Console/Order.png";
const char* Q4_NUMBER_IMAGE   = "Game/Console/Number.png";
const char* Q4_FRAME_IMAGE    = "Game/Console/Frame.png";

const int NUMBERS_FONT_SIZE = 128;
const int NUMBERS_X = SCREEN_WIDTH  / 2 - QuestionManager::QUESTION_5_MAX_NUM / 2 * NUMBERS_FONT_SIZE;
const int NUMBERS_Y = SCREEN_HEIGHT / 4;

const int ORDER_ARROW_X = SCREEN_WIDTH  / 2;
const int ORDER_ARROW_Y = SCREEN_HEIGHT / 2;

const int ANSWER_NUM = 3;
const int ANSWER_FRAME_SIZE = 256;
const int ANSWER_FRAME_START_X = SCREEN_WIDTH / 2 - ANSWER_NUM / 2 * ANSWER_FRAME_SIZE;
const int ANSWER_FRAME_Y = SCREEN_HEIGHT / 4 * 3;


ConsoleQuestion5::ConsoleQuestion5( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ),
_selecting_num( ERROR ) {
	DrawerPtr drawer = Drawer::getTask( );
	_nums_image  = drawer->getImage( Q4_NUMBER_IMAGE );
	_arrow_image = drawer->getImage( ORDER_ARROW_IMAGE );
	_frame_image = drawer->getImage( Q4_FRAME_IMAGE );

	_nums_image ->setCentral( true );
	_arrow_image->setCentral( true );
	_frame_image->setCentral( true );
}

ConsoleQuestion5::~ConsoleQuestion5( ) {
}

void ConsoleQuestion5::draw( int x, int y ) const {
	// êîéö
	for ( int i = 0; i < QuestionManager::QUESTION_5_MAX_NUM; i++ ) {
		int draw_x = NUMBERS_X + i * NUMBERS_FONT_SIZE;
		int draw_y = NUMBERS_Y;

		// 0 ÇÕîÚÇŒÇ∑ÇΩÇﬂ +1
		int rect_x = ( i + 1 ) * NUMBERS_FONT_SIZE;
		int rect_y = 0;

		_nums_image->setPos( draw_x + x, draw_y + y );
		_nums_image->setRect( rect_x, rect_y, NUMBERS_FONT_SIZE, NUMBERS_FONT_SIZE );
		_nums_image->draw( );
	}

	// ñÓàÛ
	_arrow_image->setPos( ORDER_ARROW_X + x, ORDER_ARROW_Y + y );
	_arrow_image->draw( );


	// ÉtÉåÅ[ÉÄ
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		int draw_x = ANSWER_FRAME_START_X + i * ANSWER_FRAME_SIZE;
		int draw_y = ANSWER_FRAME_Y;

		_frame_image->setPos( draw_x + x, draw_y + y );
		_frame_image->draw( );
	}


	// ëIëíÜÇÃêîéö
	for ( int i = 0; i < _select_nums.size( ); i++ ) {
		int draw_x = ANSWER_FRAME_START_X + i * ANSWER_FRAME_SIZE;
		int draw_y = ANSWER_FRAME_Y;

		// getMouseOnNum( )Ç≈ï‘Ç¡ÇƒÇ≠ÇÈêîéöÇÕê≥ÇµÇ¢ÇÃÇ≈ï‚ê≥Ç»Çµ
		int rect_x = ( _select_nums[ i ] ) * NUMBERS_FONT_SIZE;
		int rect_y = 0;

		_nums_image->setPos( draw_x + x, draw_y + y );
		_nums_image->setRect( rect_x, rect_y, NUMBERS_FONT_SIZE, NUMBERS_FONT_SIZE );
		_nums_image->draw( );
	}
}

void ConsoleQuestion5::actOnNone( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isClickDownLeft( ) ) {
		int num = getMouseOnNum( );
		if ( num != ERROR ) {
			_selecting_num = num;
			_state = STATE_PUSH;
		}
	}
}

void ConsoleQuestion5::actOnPush( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->getClickingLeft( ) > 0 ) {
		return;
	}

	int num = getMouseOnNum( );
	if ( num != _selecting_num ) {
		_state = STATE_NONE;
	} else {
		_state = STATE_PUSH_UP;
	}
}

void ConsoleQuestion5::actOnPushUp( ) {
	// âπ
	playClickSE( );


	_select_nums.push_back( _selecting_num );

	if ( _select_nums.size( ) == ANSWER_NUM ) {
		_state = STATE_ANSWER;
		_start_time = getNowCount( );
	} else {
		_state = STATE_NONE;
	}
}

void ConsoleQuestion5::actOnAnswer( ) {
	if ( getNowCount( ) - _start_time < ANSWER_WAIT_TIME ) {
		return;
	}

	bool answer = _question_manager->answerQuestion5( _select_nums[ 0 ], _select_nums[ 1 ], _select_nums[ 2 ] );

	if ( answer ) {
		playClearSE( );
		_callback( );
	} else {
		_state = STATE_NONE;
		playUnClearSE( );
		_select_nums.clear( );
	}
}

int ConsoleQuestion5::getMouseOnNum( ) const {
	MousePtr mouse = Mouse::getTask( );

	Vector mouse_pos = mouse->getPoint( );
	const int MAX_NUM = 9;
	for ( int i = 0; i < MAX_NUM; i++ ) {
		double x = NUMBERS_X + i * NUMBERS_FONT_SIZE;
		double y = NUMBERS_Y;

		if ( x - NUMBERS_FONT_SIZE / 2 < mouse_pos.x && mouse_pos.x < x + NUMBERS_FONT_SIZE / 2 &&
			 y - NUMBERS_FONT_SIZE / 2 < mouse_pos.y && mouse_pos.y < y + NUMBERS_FONT_SIZE / 2 ) {
			return i + 1;
		}
	}

	return ERROR;
}