#include "Hint.h"
#include "QuestionManager.h"

#include "Manager.h"
#include "Drawer.h"
#include "Image.h"

const char* HINT_BG_FILEPATH = "Game/UI/UIBG.png";
const char* HINT_FILEPATH    = "Resources/Hint/Q";
const int HINT_FONT_SIZE = 60;
const int HINT_COLOR = 0x000000; // 黒
const int NEW_HINT_SHOW_TIME = 60000 * 3; // 3分

Hint::Hint( QuestionManagerConstPtr question_manager ) :
_question_manager( question_manager ),
_hint_data( ),
_show_row( 1 ) {
	_bg = Drawer::getTask( )->getImage( HINT_BG_FILEPATH );
}

Hint::~Hint( ) {
}

void Hint::update( ) {
	Manager* manager = Manager::getInstance( );
	int now = manager->getNowCount( );

	_show_row = ( now - _question_manager->getHintOpenTime( ) ) / NEW_HINT_SHOW_TIME;
	_show_row += 1;

	if ( _show_row > _hint_data.data.size( ) ) {
		_show_row = ( int )_hint_data.data.size( );
	}
}

void Hint::draw( ) const {
	_bg->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	bool exist_hint = ( _hint_data.data.size( ) != 0 );
	if ( exist_hint == false ) {
		drawer->drawFormatStringCenter( SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, HINT_COLOR, HINT_FONT_SIZE, "後は脱出するだけだ!!" );
	} else {
		const int ROW = ( int )_hint_data.data.size( );
		const int COL = ( int )_hint_data.data[ 0 ].size( );
		const float X = SCREEN_WIDTH / 2.0f;
		const float Y = SCREEN_HEIGHT / 2.0f - ( ROW + COL ) / 2 * HINT_FONT_SIZE - ( ( ROW + COL ) - 1 ) / 2 * HINT_FONT_SIZE; // center - line_num - space_line

		float y = Y;
		for ( int i = 0; i < _show_row; i++ ) {
			for ( int j = 0; j < _hint_data.data[ i ].size( ); j++ ) {
				std::string message = _hint_data.data[ i ][ j ];
				drawer->drawFormatStringCenter( X, y, HINT_COLOR, HINT_FONT_SIZE, "%s", message.c_str( ) );
				y += HINT_FONT_SIZE;
			}
			// スペースを空ける
			y += HINT_FONT_SIZE;
		}
	}
}

void Hint::close( ) {
	_hint_data = CsvData( );
}

void Hint::open( ) {
	int question_num = _question_manager->getHintQuestionNum( );
	std::string path = HINT_FILEPATH;
	path += std::to_string( question_num ) + ".csv";
	_hint_data = CsvData( path.c_str( ) );
}