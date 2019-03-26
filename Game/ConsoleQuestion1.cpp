#include "ConsoleQuestion1.h"
#include "define.h"
#include "QuestionManager.h"

#include "Image.h"
#include "Drawer.h"
#include "Mouse.h"

#include <vector>

const char* QUESTION1_CONSOLE_HINT_FILEPATH = "Game/Console/Question1.png";

ConsoleQuestion1::ConsoleQuestion1( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ),
_square_state( ),
_selecting_idx( ERROR ) {
	_square = Drawer::getTask( )->getImage( QUESTION1_CONSOLE_HINT_FILEPATH );
	_square_width  = _square->getImageWidth ( ) / 2;
	_square_height = _square->getImageHeight( ) / 2;
}

ConsoleQuestion1::~ConsoleQuestion1( ) {
}

void ConsoleQuestion1::draw( int x, int y ) const {
	const int ROW = 3;
	const int COL = 3;

	const int SX = ( SCREEN_WIDTH  - _square_width * COL ) / 2;
	const int SY = ( SCREEN_HEIGHT - _square_width * ROW ) / 2;

	for ( int i = 0; i < ROW; i++ ) {
		for ( int j = 0; j < COL; j++ ) {

			int draw_x = SX + j * _square_width;
			int draw_y = SY + i * _square_width;

			int rect_x = 0;
			int rect_y = _square_height;

			// 黒白を切り替える
			int idx = i * COL + j;
			if ( _square_state[ idx ] == BLACK ) {
				rect_x = _square_width;
			} else {
				rect_x = 0;
			}
			// 右上ならかけたものを表示
			if ( i == 0 && j == COL -1 ) {
				rect_y = 0;
			}

			_square->setRect( rect_x, rect_y, _square_width, _square_height );
			_square->setPos( x + draw_x, y + draw_y );
			_square->draw( );
		}
	}
}

void ConsoleQuestion1::actOnNone( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isClickDownLeft( ) ) {
		int num = getMouseOnSquareIdx( );
		if ( num != ERROR ) {
			_state = STATE_PUSH;
			_selecting_idx = num;
		}
	}
}

void ConsoleQuestion1::actOnPush( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->getClickingLeft( ) > 0 ) {
		return;
	}

	int num = getMouseOnSquareIdx( );
	if ( num == _selecting_idx ) {
		_state = STATE_PUSH_UP;
		_square_state[ num ] = ( _square_state[ num ] ^ 1U );
	} else {
		_state = STATE_NONE;
	}
}

void ConsoleQuestion1::actOnPushUp( ) {
	// 音
	playClickSE( );

	if ( getBlackSquareNum( ) < 3 ) {
		_state = STATE_NONE;
	} else {
		_state = STATE_ANSWER;
		_start_time = getNowCount( );
	}
}

void ConsoleQuestion1::actOnAnswer( ) {
	// 黒い部分の取得
	std::vector< unsigned char > answer_idx;
	for ( int i = 0; i < _SQUARE_NUM; i++ ) {
		if ( _square_state[ i ] == BLACK ) {
			answer_idx.push_back( i );
		}
	}

	bool answer = false;
	if ( answer_idx.size( ) == 3 ) {
		answer = _question_manager->answerQuestion1( answer_idx[ 0 ], answer_idx[ 1 ], answer_idx[ 2 ] );
	}

	if ( answer ) {
		// 一定時間後にコールバック
		if ( getNowCount( ) - _start_time > ANSWER_WAIT_TIME ) {
			playClearSE( );
			_callback( );
		}
	} else {
		_state = STATE_NONE;
	}
}

int ConsoleQuestion1::getMouseOnSquareIdx( ) const {
	const int ROW = 3;
	const int COL = 3;
	const int SX = ( SCREEN_WIDTH  - _square_width * COL ) / 2;
	const int SY = ( SCREEN_HEIGHT - _square_width * ROW ) / 2;

	Vector pos = Mouse::getTask( )->getPoint( );

	if ( pos.x < SX || SX + _square_width * COL < pos.x ) {
		return ERROR;
	}
	if ( pos.y < SY || SY + _square_width * ROW < pos.y ) {
		return ERROR;
	}

	Vector adjust_pos = pos - Vector( SX, SY );
	int x = ( int )adjust_pos.x / _square_width;
	int y = ( int )adjust_pos.y / _square_width;
	
	return x + y * COL;
}

int ConsoleQuestion1::getBlackSquareNum( ) const {
	int count = 0;
	for ( unsigned char state : _square_state ) {
		if ( state == BLACK ) {
			count++;
		}
	}
	return count;
}