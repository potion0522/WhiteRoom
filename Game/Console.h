#pragma once
#include "UICanvas.h"
#include "smart_ptr.h"
#include "Mathematics.h"
#include "define.h"
#include <array>

/*******************************************************

ページを管理しているコンソールのクラス
ページからの通知を受け取ってエレベーターなどに反映する

********************************************************/

PTR( Image );
PTR( ElevatorButton );
PTR( Page );
PTR( QuestionManager );

class Console : public UICanvas {
public:
	enum PAGE_NUM {
		PAGE_NUM_1, // F1
		PAGE_NUM_2, // F2
		PAGE_NUM_3,	// F3
		PAGE_NUM_4,	// F4
		PAGE_NUM_5,	// F5
		PAGE_NUM_6,	// GF
		MAX_PAGE_NUM
	};

	enum CONSOLE_STATE {
		CONSOLE_STATE_IDLE,
		CONSOLE_STATE_SLIDE_UP,
		CONSOLE_STATE_SLIDE_DOWN,
		CONSOLE_STATE_SLIDE_LEFT,
		CONSOLE_STATE_SLIDE_RIGHT,
	};

public:
	Console( ElevatorButtonPtr, QuestionManagerPtr );
	virtual ~Console( );

public:
	void update( );
	void draw( ) const;
	void close( );
	void open( );

private:
	bool isChangeActivate( ) const;
	void changeState( CONSOLE_STATE state );
	void slidePage( int add_x, int add_y );
	void actOnIdle( );
	void actOnSlideUp( );
	void actOnSlideDown( );
	void actOnSlideLeft( );
	void actOnSlideRight( );
	void orderFloorChangeToElevator( FLOOR floor );

private:
	const PAGE_NUM _INIT_PAGE_NUM = PAGE_NUM_3;

private:
	CONSOLE_STATE _state;
	PAGE_NUM _page_num;
	Vector _slide_start_pos; // スライドの始点
	ImagePtr _bg;
	ElevatorButtonPtr _elevator_button;
	std::array< PagePtr, MAX_PAGE_NUM > _pages;
};

