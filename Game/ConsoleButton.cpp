#include "ConsoleButton.h"
#include "define.h"

#include "Button.h"
#include "Drawer.h"

#include <string>

const char* DEFAULT_BUTTON_FILEPATH = "Game/Console/Button";
const char* PUSH_BUTTON_FILEPATH    = "Game/Console/ButtonPush";

ConsoleButton::ConsoleButton( Console::PAGE_NUM page_num, const int& x, const int& y, std::function< void( ) > callback ) :
PageContent( x, y, callback ) {

	// filepath��ύX
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

	// �{�^���̐���
	_button = ButtonPtr( new Button );
	_button->setDefaultImage( default_button_filepath.c_str( ) );
	_button->setPushImage( push_button_filepath.c_str( ) );
	_button->setPos( Vector( _x, _y ) );
}

ConsoleButton::~ConsoleButton( ) {
}

void ConsoleButton::update( ) {
	// �{�^���̃A�b�v�f�[�g
	_button->update( );

	if ( _button->isClicked( ) ) {
		_callback( );
	}
}

void ConsoleButton::draw( ) const {
	// �`��ʒu�̓���
	_button->setPos( Vector( SCREEN_WIDTH / 2 + _x, SCREEN_HEIGHT / 2 + _y ) );
	_button->draw( );
}
