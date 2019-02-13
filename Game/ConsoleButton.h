#pragma once
#include "PageContent.h"
#include "smart_ptr.h"
#include "Console.h"

PTR( ConsoleButton );
PTR( Button );

class ConsoleButton : public PageContent {
public:
	ConsoleButton( Console::PAGE_NUM page_num, const int& x, const int& y, std::function< void( ) > func );
	~ConsoleButton( );

public:
	void update( );
	void draw( ) const;

private:
	int _button_width;
	int _button_height;
	ButtonPtr _button;
};

