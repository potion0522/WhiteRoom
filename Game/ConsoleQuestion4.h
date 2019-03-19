#pragma once
#include "ConsoleQuestion.h"


/*********************************************

コンソールの4Pの問題(Question4)
Day, Month は0から表現する

*********************************************/

PTR( ConsoleQuestion4 );
PTR( Image );

class ConsoleQuestion4 : public ConsoleQuestion {
private:
	enum STATE {
		STATE_NONE,
		STATE_PUSH,
		STATE_PUSH_UP,
		STATE_ANSWER
	};
	enum CLICK_TARGET {
		CLICK_TARGET_MONTH,
		CLICK_TARGET_DAY,
	};

public:
	ConsoleQuestion4( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion4( );

public:
	void update( );
	void draw( int x, int y ) const;

private:
	void actOnNone( );
	void actOnPush( );
	void actOnPushArrow( );
	void actOnPushDay( );
	void actOnPushUp( );
	void actOnPushUpArrow( );
	void actOnPushUpDay( );
	void actOnAnswer( );
	int getMouseOnArrowDir( ) const;
	int getMouseOnDay( ) const;
	int getNowCount( ) const;

private:
	const int ANSWER_WAIT_TIME = 2000; // ミリ
	const int MONTH = 12;
	const int ARROW_DIR_LEFT  = -1;
	const int ARROW_DIR_RIGHT =  1;
	const int ERROR = 0xff;

private:
	STATE _state;
	CLICK_TARGET _click_target;
	int _selecting_num;
	int _start_time;
	unsigned char _select_month;
	unsigned char _select_day;
	ImagePtr _frame_image;
	ImagePtr _nums_image;
	ImagePtr _arrow;
};

