#include "Page.h"
#include "define.h"
#include "ConsoleButton.h"
#include "ConsoleQuestion1.h"

#include "Drawer.h"

Page::Page( Console::PAGE_NUM page_num, std::function< void( FLOOR ) > func_button_push, QuestionManagerConstPtr question_manager ) :
_page_num( page_num ),
_x( 0 ),
_y( 0 ),
_view_x( 0 ),
_view_y( 0 ),
_slide_x( 0 ),
_slide_y( 0 ),
_func_button_push( func_button_push ) {
	// 初期化
	switch ( _page_num ) {
		case Console::PAGE_NUM_1:
			_y = CONSOLE_HEIGHT * 0;
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_2:
			_y = CONSOLE_HEIGHT * 1;
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_3:
			_y = CONSOLE_HEIGHT * 2;
			_content = ConsoleQuestion1Ptr( new ConsoleQuestion1( [ & ] { callbackAnswer( ); }, question_manager ) );
			break;
		case Console::PAGE_NUM_4:
			_y = CONSOLE_HEIGHT * 3;
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_5:
			_y = CONSOLE_HEIGHT * 4;
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_6:
			_x = CONSOLE_WIDTH;
			_y = CONSOLE_HEIGHT * 3;
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
	}

}

Page::~Page( ) {
}

void Page::update( ) {
	_content->update( );
}

void Page::draw( ) const {
	_content->draw( _view_x, _view_y );
}

void Page::slide( int add_x, int add_y ) {
	_slide_x += add_x;
	_slide_y += add_y;
	_view_x = _x + _slide_x;
	_view_y = _y + _slide_y;
}

void Page::callbackPushButton( ) {
	// ボタンが押されたとき、そのフロア番号を渡す
	if ( _page_num == Console::PAGE_NUM_6 ) {
		_func_button_push( FLOOR_GF );
	} else {
		_func_button_push( ( FLOOR )( FLOOR_1 + _page_num ) );
	}
}

void Page::callbackAnswer( ) {
	switch ( _page_num ) {
		case Console::PAGE_NUM_1:
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_2:
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_3:
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_4:
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_5:
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
		case Console::PAGE_NUM_6:
			_content = ConsoleButtonPtr( new ConsoleButton( _page_num, [ & ] { callbackPushButton( ); } ) );
			break;
	}
}