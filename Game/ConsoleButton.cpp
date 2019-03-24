#include "ConsoleButton.h"
#include "define.h"

#include "Button.h"
#include "Drawer.h"

#include <string>

const char* DEFAULT_BUTTON_FILEPATH = "Game/Console/Button";
const char* PUSH_BUTTON_FILEPATH    = "Game/Console/ButtonPush";

const char* BUTTON_TAG = "FloorChange";

ConsoleButton::ConsoleButton( Console::PAGE_NUM page_num, std::function< void( ) > callback ) :
PageContent( callback ) {

	// filepathを変更
	std::string floor_num;
	switch ( page_num ) {
		case Console::PAGE_NUM_1:
			floor_num = "B1.png";
			break;
		case Console::PAGE_NUM_2:
			floor_num = "B2.png";
			break;
		case Console::PAGE_NUM_3:
			floor_num = "B3.png";
			break;
		case Console::PAGE_NUM_4:
			floor_num = "B4.png";
			break;
		case Console::PAGE_NUM_5:
			floor_num = "B5.png";
			break;
		case Console::PAGE_NUM_6:
			floor_num = "GF.png";
			break;
	}
	std::string default_button_filepath = DEFAULT_BUTTON_FILEPATH + floor_num;
	std::string push_button_filepath    = PUSH_BUTTON_FILEPATH + floor_num;

	// ボタンの生成
	_button = ButtonPtr( new Button( BUTTON_TAG, [ & ]( const char* tag ) { _callback( ); } ) );
	_button->setDefaultImage( default_button_filepath.c_str( ) );
	_button->setPushImage( push_button_filepath.c_str( ) );
}

ConsoleButton::~ConsoleButton( ) {
}

void ConsoleButton::update( ) {
	// ボタンのアップデート
	_button->update( );
}

void ConsoleButton::draw( int x, int y ) const {
	// 描画位置の同期
	_button->setPos( Vector( SCREEN_WIDTH / 2 + x, SCREEN_HEIGHT / 2 + y ) );
	_button->draw( );
}
