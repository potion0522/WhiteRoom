#pragma once
#include "PageContent.h"
#include "smart_ptr.h"
#include "Console.h"

/********************************************************

ボタンの押下の検知を行う

********************************************************/

PTR( ConsoleButton );
PTR( Button );

class ConsoleButton : public PageContent {
public:
	ConsoleButton( Console::PAGE_NUM page_num, std::function< void( ) > callback );
	~ConsoleButton( );

public:
	void update( );
	void draw( int x, int y ) const;

private:
	int _button_width;
	int _button_height;
	ButtonPtr _button;
};

