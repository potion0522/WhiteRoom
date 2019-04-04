#include "ConsoleQuestion2.h"
#include "QuestionManager.h"

#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"
#include "Random.h"

// 1.club 2.heart 3.diamont 4.spade
const char* IMAGE_FILE = "Game/UI/Console/Marks.png";

const int Q2_MARK_SIZE = 256;
const float Q2_CIRCLE_RADIUS = Q2_MARK_SIZE * 0.8f;

ConsoleQuestion2::ConsoleQuestion2( std::function< void( ) > callback, QuestionManagerPtr question_manager ) :
ConsoleQuestion( callback, question_manager, 2 ) {
	DrawerPtr drawer = Drawer::getTask( );
	_mark_image = drawer->getImage( IMAGE_FILE );
	_mark_image->setCentral( true );

	RandomPtr random = Random::getTask( );
	const int MAX_COLOR = 3;

	int init = 0;
	while ( init < ANSWER_NUM ) {
		int color_idx = random->getRand( 1, MAX_COLOR );

		bool insert = true;
		// 色の並び順もランダム
		for ( int i = 0; i < ANSWER_NUM; i++ ) {
			if ( _mark_state[ i ].first == color_idx ) {
				insert = false;
				break;
			}
		}

		if ( insert ) {
			_mark_state[ init ].first = color_idx;
			_mark_state[ init ].second = 0x00;
			init++;
		}
	}

	_circle_to_circle_space = ( SCREEN_WIDTH / ( ANSWER_NUM + 1 ) );
}

ConsoleQuestion2::~ConsoleQuestion2( ) {
}

void ConsoleQuestion2::draw( int x, int y ) const {
	// 円
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		float draw_x = ( float )( _circle_to_circle_space + i * _circle_to_circle_space );
		float draw_y = SCREEN_HEIGHT / 2;

		int color;
		switch ( _mark_state[ i ].first ) {
			case SPHERE_COLOR_RED:
				color = 0xff0000;
				break;
			case SPHERE_COLOR_GREEN:
				color = 0x00ff00;
				break;
			case SPHERE_COLOR_BLUE:
				color = 0x0000ff;
				break;
			default:
				color = 0xffffff;
				break;
		}

		drawer->drawCircle( draw_x + x, draw_y + y, Q2_CIRCLE_RADIUS, color, true );
	}

	// マーク
	for ( int i = 0; i < ANSWER_NUM; i++ ) {
		// 座標
		int draw_x = ( _circle_to_circle_space + i * _circle_to_circle_space );
		int draw_y = SCREEN_HEIGHT / 2;

		// rect
		int rect_x = _mark_state[ i ].second * Q2_MARK_SIZE;
		int rect_y = 0;
		int width  = Q2_MARK_SIZE;
		int height = Q2_MARK_SIZE;

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
		double circle_x = ( double )( _circle_to_circle_space + i * _circle_to_circle_space );
		double circle_y = SCREEN_HEIGHT / 2;

		Vector circle_pos = Vector( circle_x, circle_y );
		if ( ( circle_pos - pos ).getLength2( ) < Q2_CIRCLE_RADIUS * Q2_CIRCLE_RADIUS ) {
			_mark_state[ i ].second = ( _mark_state[ i ].second + 1 ) % QuestionManager::QUESTION_2_MAX_MARK_NUM;
			break;
		}
	}
	// 音
	playClickSE( );


	_state = STATE_ANSWER;
	_start_time = getNowCount( );
}

void ConsoleQuestion2::actOnAnswer( ) {
	const int MAX_COLOR = 3;
	std::array< unsigned char, MAX_COLOR > answer;

	// rgbの順にする
	for ( int i = 0; i < MAX_COLOR; i++ ) {
		int mark;
		int color_idx = i + 1;

		if ( _mark_state[ 0 ].first == color_idx ) {
			mark = _mark_state[ 0 ].second;
		}
		if ( _mark_state[ 1 ].first == color_idx ) {
			mark = _mark_state[ 1 ].second;
		}
		if ( _mark_state[ 2 ].first == color_idx ) {
			mark = _mark_state[ 2 ].second;
		}

		answer[ i ] = mark;
	}
	bool result = _question_manager->answerQuestion2( answer[ 0 ], answer[ 1 ], answer[ 2 ] );

	if ( result ) {
		// クリア後一定時間待機
		if ( getNowCount( ) - _start_time > ANSWER_WAIT_TIME ) {
			clear( );
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
		double circle_x = ( double )( _circle_to_circle_space + i * _circle_to_circle_space );
		double circle_y = SCREEN_HEIGHT / 2;

		Vector circle_pos = Vector( circle_x, circle_y );
		if ( ( circle_pos - pos ).getLength2( ) < Q2_CIRCLE_RADIUS * Q2_CIRCLE_RADIUS ) {
			on_button = true;
			break;
		}
	}

	return on_button;
}
