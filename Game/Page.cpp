#include "Page.h"
#include "define.h"

#include "Drawer.h"

Page::Page( Console::PAGE_NUM page_num ) :
_page_num( page_num ),
_x( 0 ),
_y( 0 ) {
	// ‰Šú‰»
	switch ( page_num ) {
		case Console::PAGE_NUM_1:
			_y = CONSOLE_HEIGHT * 0;
			break;
		case Console::PAGE_NUM_2:
			_y = CONSOLE_HEIGHT * 1;
			break;
		case Console::PAGE_NUM_3:
			_y = CONSOLE_HEIGHT * 2;
			break;
		case Console::PAGE_NUM_4:
			_y = CONSOLE_HEIGHT * 3;
			break;
		case Console::PAGE_NUM_5:
			_y = CONSOLE_HEIGHT * 4;
			break;
		case Console::PAGE_NUM_6:
			_x = CONSOLE_WIDTH;
			_y = CONSOLE_HEIGHT * 3;
			break;
	}

}

Page::~Page( ) {
}

void Page::update( ) {
}

void Page::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawFormatString( ( float )_x, ( float )_y, 0xff0000, "PAGE : %d ", _page_num );
}

void Page::slide( int add_x, int add_y ) {
	_x += add_x;
	_y += add_y;
}