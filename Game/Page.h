#pragma once
#include "smart_ptr.h"
#include "Console.h"
#include <functional>

PTR( Page );
PTR( PageContent );

class Page {
public:
	Page( Console::PAGE_NUM page_num, std::function< void( int ) > func );
	virtual ~Page( );

public:
	void update( );
	void draw( ) const;

	void slide( int add_x, int add_y );

private:
	void callbackPushButton( );
	void callbackAnswer( );

private:
	Console::PAGE_NUM _page_num;
	int _x;
	int _y;
	PageContentPtr _content;
	std::function< void( int ) > _func_button_push;
};

