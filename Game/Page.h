#pragma once
#include "smart_ptr.h"
#include "Console.h"
#include <functional>

/********************************************************

�R���\�[����1�y�[�W�����Ǘ�����N���X

��肩�{�^���ǂ��炩��ێ����A�؂�ւ���
�{�^���̉������R���\�[���ɒʒm���邽�߂̃N���X

********************************************************/


PTR( Page );
PTR( PageContent );

class Page {
public:
	Page( Console::PAGE_NUM page_num, std::function< void( FLOOR ) > func_button_push, QuestionManagerPtr question_manager );
	virtual ~Page( );

public:
	void update( );
	void draw( ) const;

	void slide( int add_x, int add_y );
	void refreshExceptForAnswer( );

private:
	void callbackPushButton( );
	void callbackAnswer( );

private:
	Console::PAGE_NUM _page_num;
	int _x;
	int _y;
	int _slide_x;
	int _slide_y;

	int _view_x;
	int _view_y;
	PageContentPtr _content;
	std::function< void( FLOOR ) > _func_button_push;
};

