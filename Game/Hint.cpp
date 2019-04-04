#include "Hint.h"
#include "QuestionManager.h"
#include "Debug.h"

#include "Manager.h"
#include "Drawer.h"
#include "Image.h"

const char* HINT_BG_FILEPATH = "Game/UI/UIBG.png";
const char* HINT_FILEPATH    = "Resources/Hint/Q";
const int NEW_HINT_SHOW_TIME = 60000 * 3; // 3ï™

Hint::Hint( QuestionManagerConstPtr question_manager ) :
_question_manager( question_manager ),
_hint_data( ),
_show_time( NEW_HINT_SHOW_TIME ),
_show_row( 1 ) {
	_bg = Drawer::getTask( )->getImage( HINT_BG_FILEPATH );
}

Hint::~Hint( ) {
}

void Hint::update( ) {
	updateRow( );
	updateTime( );
}

void Hint::draw( ) const {
	// îwåi
	_bg->draw( );

	// ÉqÉìÉgì‡óe
	const int HINT_FONT_SIZE = 60;
	const int HINT_COLOR = 0x000000; // çï
	DrawerPtr drawer = Drawer::getTask( );

	bool exist_hint = ( _hint_data.data.size( ) != 0 );

	if ( exist_hint == false ) {
		drawer->drawFormatStringCenter( SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, HINT_COLOR, HINT_FONT_SIZE, "å„ÇÕíEèoÇ∑ÇÈÇæÇØÇæ!!" );
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
			// ÉXÉyÅ[ÉXÇãÛÇØÇÈ
			y += HINT_FONT_SIZE;
		}
	}

	// écÇËéûä‘
	const int SHOW_TIME_COLOR = 0xff0000; // ê‘
	const int SHOW_TIME_FONT_SIZE = 30;
	std::string str = "éüÇÃÉqÉìÉgÇÃäJé¶Ç‹Ç≈ : ";
	str += std::to_string( _show_time ) + "ïb";
	float x = ( float )( SCREEN_WIDTH - drawer->getStringWidth( str.c_str( ), SHOW_TIME_FONT_SIZE ) - SHOW_TIME_FONT_SIZE ); // width - font_width - space
	drawer->drawFormatString( x, HINT_FONT_SIZE, SHOW_TIME_COLOR, SHOW_TIME_FONT_SIZE, "%s", str.c_str( ) );
}

void Hint::close( ) {
	_hint_data = CsvData( );
}

void Hint::open( ) {
	int question_num = _question_manager->getHintQuestionNum( );
	std::string path = HINT_FILEPATH;
	path += std::to_string( question_num ) + ".csv";
	_hint_data = CsvData( path.c_str( ) );

	
	updateRow( );
	updateTime( );
}

void Hint::updateRow( ) {
	Manager* manager = Manager::getInstance( );
	const int NOW = manager->getNowCount( );
	const int QUESTION_HINT_OPEN_TIME = _question_manager->getHintOpenTime( );

	// row
	int row = ( NOW - QUESTION_HINT_OPEN_TIME ) / NEW_HINT_SHOW_TIME;
	if ( row < _hint_data.data.size( ) ) {
		_show_row = row + 1;
	} else {
		_show_row = ( int )_hint_data.data.size( );
	}
}

void Hint::updateTime( ) {
	Manager* manager = Manager::getInstance( );
	const int NOW = manager->getNowCount( );
	const int ONE_SEC = 1000;
	const int QUESTION_HINT_OPEN_TIME = _question_manager->getHintOpenTime( );

	// time
	int show_time = ( NEW_HINT_SHOW_TIME - ( NOW - ( QUESTION_HINT_OPEN_TIME + ( _show_row - 1 ) * NEW_HINT_SHOW_TIME ) ) ) / ONE_SEC;
	if ( show_time >= 0 && _show_row < _hint_data.data.size( ) ) {
		_show_time = show_time;
	} else {
		_show_time = 0;
	}
}