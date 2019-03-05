#pragma once
#include "smart_ptr.h"
#include "Console.h"
#include <functional>

/********************************************************

コンソールの1ページ分を管理するクラス

問題かボタンどちらかを保持し、切り替える
ボタンの押下をコンソールに通知するためのクラス

********************************************************/


PTR( Page );
PTR( PageContent );

class Page {
public:
	Page( Console::PAGE_NUM page_num, std::function< void( FLOOR ) > func_button_push, QuestionManagerConstPtr question_manager );
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
	std::function< void( FLOOR ) > _func_button_push;
};

