#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include "define.h"
#include <array>

/*

ページを管理しているコンソールのクラス
ページからの通知を受け取ってエレベーターなどに反映する

*/

PTR( Image );
PTR( ElevatorButton );
PTR( Page );
PTR( ConsoleObserver );
PTR( ConsoleActiveObservable );

class Console {
public:
	enum PAGE_NUM {
		PAGE_NUM_1,
		PAGE_NUM_2,
		PAGE_NUM_3,
		PAGE_NUM_4,
		PAGE_NUM_5,
		PAGE_NUM_6,
		MAX_PAGE_NUM
	};

	enum CONSOLE_STATE {
		CONSOLE_STATE_NONE,
		CONSOLE_STATE_OPENING,
		CONSOLE_STATE_CLOSING,
		CONSOLE_STATE_IDLE,
		CONSOLE_STATE_SLIDE_UP,
		CONSOLE_STATE_SLIDE_DOWN,
		CONSOLE_STATE_SLIDE_LEFT,
		CONSOLE_STATE_SLIDE_RIGHT,
	};

public:
	Console( ElevatorButtonPtr elevator_button );
	virtual ~Console( );

public:
	void update( );
	void draw( ) const;
	ConsoleActiveObservablePtr getActiveObservable( ) const;

private:
	bool isChangeActivate( ) const;
	void changeState( CONSOLE_STATE state );
	void slidePage( int add_x, int add_y );
	void actOnNone( );
	void actOnIdle( );
	void actOnOpening( );
	void actOnClosing( );
	void actOnSlideUp( );
	void actOnSlideDown( );
	void actOnSlideLeft( );
	void actOnSlideRight( );
	void orderFloorChangeToElevator( FLOOR floor );

private:
	CONSOLE_STATE _state;
	PAGE_NUM _page_num;
	Vector _slide_start_pos;
	Vector _slide_end_pos;
	ImagePtr _bg;
	ElevatorButtonPtr _elevator_button;
	std::array< PagePtr, MAX_PAGE_NUM > _pages;
	ConsoleObserverPtr _observer;
};

