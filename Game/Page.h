#pragma once
#include "smart_ptr.h"
#include "Console.h"

PTR( Page );

class Page {
public:
	Page( Console::PAGE_NUM page_num );
	virtual ~Page( );

public:
	void update( );
	void draw( ) const;

	void slide( int add_x, int add_y );

private:
	Console::PAGE_NUM _page_num;
	int _x;
	int _y;
};

