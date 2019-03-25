#include "ConsoleQuestion3.h"
#include "QuestionManager.h"

#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"

const char* NUMS_IMAGE  = "Game/Console/Number.png";
const char* HINT_IMAGE  = "Game/Console/Question3Hint";
const char* FRAME_IMAGE = "Game/Console/Frame.png";

const int FRAME_SIZE = 256;
const int NUMS_SIZE  = 128;
const int MAX_NUM = 10;
const int NUMS_ROW = 2;
const int NUMS_COL = 5;

const int ANSWER_FRAME_X = SCREEN_WIDTH / 2 + ( SCREEN_WIDTH / 2 - FRAME_SIZE * 3 ) / 2 + FRAME_SIZE / 2;
const int ANSWER_FRAME_Y = SCREEN_HEIGHT / 4 * 3;
const int NUMS_START_X = ( SCREEN_WIDTH / 2 + ( SCREEN_WIDTH / 2 - NUMS_SIZE * NUMS_COL ) / 2 ) + NUMS_SIZE / 2;
const int NUMS_START_Y = ( ( SCREEN_HEIGHT / 2 - NUMS_SIZE * NUMS_ROW ) / 2 )                   + NUMS_SIZE / 2;

ConsoleQuestion3::ConsoleQuestion3( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ),
_selecting_num( 0x00 ) {
	bool arrow_up = ( question_manager->getHintQuestion3Arrow( ) > 0 ? true : false );
	std::string hint_image_path = HINT_IMAGE;
	if ( arrow_up ) {
		hint_image_path += "Up.png";
	} else {
		hint_image_path += "Down.png";
	}

	DrawerPtr drawer = Drawer::getTask( );
	_nums_image  = drawer->getImage( NUMS_IMAGE );
	_hint_image  = drawer->getImage( hint_image_path.c_str( ) );
	_frame_image = drawer->getImage( FRAME_IMAGE );

	_nums_image ->setCentral( true );
	_frame_image->setCentral( true );
}

ConsoleQuestion3::~ConsoleQuestion3( ) {
}

void ConsoleQuestion3::draw( int x, int y ) const {
	// nums(全表記)
	for ( int i = 0; i < MAX_NUM; i++ ) {
		int draw_x = NUMS_START_X + ( i % NUMS_COL ) * NUMS_SIZE;
		int draw_y = NUMS_START_Y + i / ( MAX_NUM / NUMS_ROW ) * NUMS_SIZE;
		int rect_x = i * NUMS_SIZE;
		int rect_y = 0;
		_nums_image->setPos( draw_x + x, draw_y + y );
		_nums_image->setRect( rect_x, rect_y, NUMS_SIZE, NUMS_SIZE );
		_nums_image->draw( );
	}

	// nums(選択中)
	for ( int i = 0; i < _select_nums.size( ); i++ ) {
		int draw_x = ANSWER_FRAME_X + i * FRAME_SIZE;
		int draw_y = ANSWER_FRAME_Y;
		int rect_x = _select_nums[ i ] * NUMS_SIZE;
		int rect_y = 0;
		_nums_image->setPos( draw_x + x, draw_y + y );
		_nums_image->setRect( rect_x, rect_y, NUMS_SIZE, NUMS_SIZE );
		_nums_image->draw( );
	}


	// frame
	for ( int i = 0; i < MAX_SELECT_NUM; i++ ) {
		int draw_x = ANSWER_FRAME_X + i * FRAME_SIZE;
		int draw_y = ANSWER_FRAME_Y;
		_frame_image->setPos( draw_x + x, draw_y + y );
		_frame_image->draw( );
	}

	// hint
	_hint_image->setPos( x, y );
	_hint_image->draw( );
}

void ConsoleQuestion3::actOnNone( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isClickDownLeft( ) ) {
		unsigned char select_num = getMouseOnNum( );
		if ( select_num != ERROR_NUM ) {
			_selecting_num = select_num;
			_state = STATE_PUSH;
		}
	}
}

void ConsoleQuestion3::actOnPush( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->getClickingLeft( ) < 1 ) {
		unsigned char select_num = getMouseOnNum( );

		// 離したときの数字が押下時と同じかどうか
		if ( select_num == _selecting_num ) {
			_state = STATE_PUSH_UP;
		} else {
			_state = STATE_NONE;
		}
	}
}

void ConsoleQuestion3::actOnPushUp( ) {
	// 音
	playClickSE( );

	_select_nums.push_back( _selecting_num );
	if ( _select_nums.size( ) == MAX_SELECT_NUM ) {
		_state = STATE_ANSWER;
		_start_time = getNowCount( );
	} else {
		_state = STATE_NONE;
	}
}

void ConsoleQuestion3::actOnAnswer( ) {
	bool answer = _question_manager->answerQuestion3( _select_nums[ 0 ], _select_nums[ 1 ], _select_nums[ 2 ] );

	if ( answer ) {
		// クリア後一定時間待機
		if ( getNowCount( ) - _start_time > ANSWER_WAIT_TIME ) {
			_callback( );
		}
	} else {
		_state = STATE_NONE;
		_select_nums.clear( );
	}
}

unsigned char ConsoleQuestion3::getMouseOnNum( ) const {
	MousePtr mouse = Mouse::getTask( );
	Vector mouse_pos = mouse->getPoint( );

	for ( int i = 0; i < MAX_NUM; i++ ) {
		int num_x = NUMS_START_X + ( i % NUMS_COL ) * NUMS_SIZE;
		int num_y = NUMS_START_Y + i / ( MAX_NUM / NUMS_ROW ) * NUMS_SIZE;
		int mouse_pos_x = ( int )mouse_pos.x;
		int mouse_pos_y = ( int )mouse_pos.y;

		if ( num_x - NUMS_SIZE / 2 < mouse_pos_x && mouse_pos_x < num_x + NUMS_SIZE / 2 &&
			 num_y - NUMS_SIZE / 2 < mouse_pos_y && mouse_pos_y < num_y + NUMS_SIZE / 2 ) {
			return i;
		}
	}
	return ERROR_NUM;
}