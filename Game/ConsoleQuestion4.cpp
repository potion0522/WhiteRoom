#include "ConsoleQuestion4.h"
#include "QuestionManager.h"

#include "Manager.h"
#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"

const char* DAY_FRAME_IMAGE = "Game/Console/DayFrame.png";
const char* MONTH_NUM_IMAGE = "Game/Console/Number.png";
const char* CHANGE_MONTH_ARROW_IMAGE = "Game/Console/Question4Arrow.png";
const char* MONDAY_IMAGE = "Game/Console/Mon.png";

const int MONTH_NUM_SIZE = 128;
const int DAY_SQUARE_SIZE = 128;
const int CHANGE_ARROW_SIZE = 256;
const int MONDAY_IMAGE_SIZE = 128;
const int DAY_FRAME_SIZE = 5;
const int DAY_COL = 7;
const int DAY_ROW = 5;

const int MONTH_X = SCREEN_WIDTH / 2 - MONTH_NUM_SIZE / 2;
const int MONTH_Y = SCREEN_HEIGHT / 8;
const int LEFT_ARROW_X  = SCREEN_WIDTH / 2 - ( int )( CHANGE_ARROW_SIZE * 1.5 );
const int RIGHT_ARROW_X = SCREEN_WIDTH / 2 + ( int )( CHANGE_ARROW_SIZE * 1.5 );
const int ARROW_Y = MONTH_Y;
const int DAY_SQUARE_START_X = ( SCREEN_WIDTH  - DAY_COL * ( DAY_SQUARE_SIZE - DAY_FRAME_SIZE ) ) / 2 + DAY_SQUARE_SIZE / 2;
const int DAY_SQUARE_START_Y = ( MONTH_Y + ( SCREEN_HEIGHT - MONTH_Y ) / DAY_ROW ) + DAY_SQUARE_SIZE;

ConsoleQuestion4::ConsoleQuestion4( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ),
_click_target( CLICK_TARGET_MONTH ),
_selecting_num( ERROR ),
_select_month( 0x00 ),
_select_day( ERROR ) {
	DrawerPtr drawer = Drawer::getTask( );
	_frame_image  = drawer->getImage( DAY_FRAME_IMAGE );
	_nums_image   = drawer->getImage( MONTH_NUM_IMAGE );
	_arrow_image  = drawer->getImage( CHANGE_MONTH_ARROW_IMAGE );
	_monday_image = drawer->getImage( MONDAY_IMAGE );

	_frame_image ->setCentral( true );
	_nums_image  ->setCentral( true );
	_arrow_image ->setCentral( true );
	_monday_image->setCentral( true );
}

ConsoleQuestion4::~ConsoleQuestion4( ) {
}

void ConsoleQuestion4::draw( int x, int y ) const {
	// 矢印
	{
		// 左
		_arrow_image->setFlipX( true );
		_arrow_image->setPos( LEFT_ARROW_X + x, ARROW_Y + y );
		_arrow_image->draw( );

		// 右
		_arrow_image->setFlipX( false );
		_arrow_image->setPos( RIGHT_ARROW_X + x, ARROW_Y + y );
		_arrow_image->draw( );
	}

	// 月
	int select_month = _select_month + 1;
	for ( int i = 0; i < 2; i++ ) {
		int drwa_x = ( MONTH_X + MONTH_NUM_SIZE ) - i * MONTH_NUM_SIZE;
		int drwa_y = MONTH_Y;

		int num = select_month % 10;
		int rect_x = num * MONTH_NUM_SIZE;
		int rect_y = 0;

		select_month /= 10;

		_nums_image->setRect( rect_x, rect_y, MONTH_NUM_SIZE, MONTH_NUM_SIZE );
		_nums_image->setPos( drwa_x + x, drwa_y + y );
		_nums_image->draw( );
	}


	// 日
	for ( int i = 0; i < DAY_IN_MONTH[ _select_month ]; i++ ) {
		int col = ( i % DAY_COL );
		int row = ( i / DAY_COL );

		int draw_x = DAY_SQUARE_START_X + col * ( DAY_SQUARE_SIZE - DAY_FRAME_SIZE );
		int draw_y = DAY_SQUARE_START_Y + row * ( DAY_SQUARE_SIZE - DAY_FRAME_SIZE );
		_frame_image->setPos( draw_x + x, draw_y + y );
		_frame_image->draw( );
	}

	// 曜日(月)
	{
		int draw_x = DAY_SQUARE_START_X;
		int draw_y = DAY_SQUARE_START_Y - MONDAY_IMAGE_SIZE;
		_monday_image->setPos( draw_x + x, draw_y + y );
		_monday_image->draw( );
	}

	// 選択中の日
	if ( _select_day != ERROR ) {
		int col = ( _select_day % DAY_COL );
		int row = ( _select_day / DAY_COL );
		int draw_x = DAY_SQUARE_START_X + col * ( DAY_SQUARE_SIZE - DAY_FRAME_SIZE );
		int draw_y = DAY_SQUARE_START_Y + row * ( DAY_SQUARE_SIZE - DAY_FRAME_SIZE );
		const int RADIUS = 30;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->drawCircle( ( float )( draw_x + x ), ( float )( draw_y + y ), RADIUS, 0xff0000, true );
	}
}

void ConsoleQuestion4::actOnNone( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( !mouse->isClickDownLeft( ) ) {
		return;
	}

	// 月か日かを判断
	Vector pos = mouse->getPoint( );

	if ( pos.y < MONTH_Y + MONTH_NUM_SIZE / 2 ) {
		// 月
		_click_target = CLICK_TARGET_MONTH;
		_selecting_num = getMouseOnArrowDir( );
	} else {
		// 日
		_click_target = CLICK_TARGET_DAY;
		_selecting_num = getMouseOnDay( );
	}

	if ( _selecting_num != ERROR ) {
		_state = STATE_PUSH;
	}
}

void ConsoleQuestion4::actOnPush( ) {
	MousePtr mouse = Mouse::getTask( );
	// クリック中は何もしない
	if ( mouse->getClickingLeft( ) > 0 ) {
		return;
	}
	
	if ( _click_target == CLICK_TARGET_MONTH ) {
		actOnPushArrow( );
	} else {
		actOnPushDay( );
	}
}

void ConsoleQuestion4::actOnPushArrow( ) {
	int num = getMouseOnArrowDir( );
	if ( num != _selecting_num ) {
		_state = STATE_NONE;
	} else {
		int next = ( num == ARROW_DIR_LEFT ? MONTH - 1 : 1 );
		_select_month = ( _select_month + next ) % MONTH;
		_state = STATE_PUSH_UP;
	}
}

void ConsoleQuestion4::actOnPushDay( ) {
	int num = getMouseOnDay( );
	if ( num != _selecting_num ) {
		_state = STATE_NONE;
	} else {
		_select_day = num;
		_start_time = getNowCount( );
		_state = STATE_PUSH_UP;
	}
}

void ConsoleQuestion4::actOnPushUp( ) {
	if ( _click_target == CLICK_TARGET_MONTH ) {
		actOnPushUpArrow( );
	} else {
		actOnPushUpDay( );
	}
}

void ConsoleQuestion4::actOnPushUpArrow( ) {
	_state = STATE_NONE;
}

void ConsoleQuestion4::actOnPushUpDay( ) {
	if ( getNowCount( ) - _start_time > ANSWER_WAIT_TIME ) {
		_state = STATE_ANSWER;
	}
}

void ConsoleQuestion4::actOnAnswer( ) {
	bool answer = _question_manager->answerQuestion4( _select_month + 1, _select_day + 1 );
	_state = STATE_NONE;
	_select_day = ERROR;

	if ( answer ) {
		_callback( );
	}
}

int ConsoleQuestion4::getMouseOnArrowDir( ) const {
	MousePtr mouse = Mouse::getTask( );
	Vector mouse_pos = mouse->getPoint( );

	// 左
	if ( ( mouse_pos - Vector( LEFT_ARROW_X, ARROW_Y ) ).getLength2( ) < pow( CHANGE_ARROW_SIZE / 2, 2 ) ) {
		return ARROW_DIR_LEFT;
	}
	// 右
	if ( ( mouse_pos - Vector( RIGHT_ARROW_X, ARROW_Y ) ).getLength2( ) < pow( CHANGE_ARROW_SIZE / 2, 2 ) ) {
		return ARROW_DIR_RIGHT;
	}

	return ERROR;
}

int ConsoleQuestion4::getMouseOnDay( ) const {
	MousePtr mouse = Mouse::getTask( );
	Vector mouse_pos = mouse->getPoint( );
	
	for ( int i = 0; i < DAY_IN_MONTH[ _select_month ]; i++ ) {
		int col = ( i % DAY_COL );
		int row = ( i / DAY_COL );

		int x = DAY_SQUARE_START_X + col * ( DAY_SQUARE_SIZE - DAY_FRAME_SIZE );
		int y = DAY_SQUARE_START_Y + row * ( DAY_SQUARE_SIZE - DAY_FRAME_SIZE );

		if ( ( mouse_pos - Vector( x, y ) ).getLength2( ) < pow( DAY_SQUARE_SIZE / 2, 2 ) ) {
			return i;
		}
	}

	return ERROR;
}