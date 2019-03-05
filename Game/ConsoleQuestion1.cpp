#include "ConsoleQuestion1.h"
#include "define.h"
#include "QuestionManager.h"

#include "Image.h"
#include "Drawer.h"
#include "Mouse.h"

#include <vector>

const char* QUESTION1_CONSOLE_HINT_FILEPATH = "Game/Console/Question/Question1.png";

ConsoleQuestion1::ConsoleQuestion1( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ),
_square_state( ) {
	_square = Drawer::getTask( )->getImage( QUESTION1_CONSOLE_HINT_FILEPATH );
	_square_width = _square->getImageWidth( ) / 2;
}

ConsoleQuestion1::~ConsoleQuestion1( ) {
}

void ConsoleQuestion1::update( ) {
	if ( updateState( ) ) {
		checkAnswer( );
	}
}

bool ConsoleQuestion1::updateState( ) {
	if ( isClicked( ) ) {
		// ƒNƒŠƒbƒN‚³‚ê‚½”Ô†‚Ìæ“¾
		int click_idx = getClickIdx( );
		if ( click_idx != -1 ) {
			_square_state[ click_idx ] = ( _square_state[ click_idx ] ^ 1U );
			return true;
		}
	}
	return false;
}

void ConsoleQuestion1::checkAnswer( ) {
	// •‚¢•”•ª‚Ìæ“¾
	std::vector< unsigned char > answer;
	for ( int i = 0; i < _SQUARE_NUM; i++ ) {
		if ( _square_state[ i ] == _BLACK ) {
			answer.push_back( i );
		}
	}

	if ( answer.size( ) == 3 ) {
		bool result = _question_manager->answerQuestion1( answer[ 0 ], answer[ 1 ], answer[ 2 ] );
		if ( result ) {
			_callback( );
		}
	}

}

bool ConsoleQuestion1::isClicked( ) const {
	return Mouse::getTask( )->isClickUpLeft( );
}

int ConsoleQuestion1::getClickIdx( ) const {
	const int ROW = 3;
	const int COL = 3;
	const int SX = ( SCREEN_WIDTH  - _square_width * COL ) / 2;
	const int SY = ( SCREEN_HEIGHT - _square_width * ROW ) / 2;

	Vector pos = Mouse::getTask( )->getPoint( );

	const int ERROR = -1;

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

void ConsoleQuestion1::draw( int x, int y ) const {
	const int ROW = 3;
	const int COL = 3;

	const int SX = ( SCREEN_WIDTH  - _square_width * COL ) / 2;
	const int SY = ( SCREEN_HEIGHT - _square_width * ROW ) / 2;

	for ( int i = 0; i < ROW; i++ ) {
		for ( int j = 0; j < COL; j++ ) {
			int idx = i * COL + j;

			// •”’‚ğØ‚è‘Ö‚¦‚é
			if ( _square_state[ idx ] == _BLACK ) {
				_square->setRect( _square_width, 0, _square_width, _square_width );
			}
			if ( _square_state[ idx ] == _WHITE ) {
				_square->setRect( 0, 0, _square_width, _square_width );
			}

			int draw_x = SX + j * _square_width;
			int draw_y = SY + i * _square_width;
			_square->setPos( x + draw_x, y + draw_y );
			_square->draw( );
		}
	}
}