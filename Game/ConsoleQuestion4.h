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
	enum CLICK_TARGET {
		CLICK_TARGET_MONTH,
		CLICK_TARGET_DAY,
	};

public:
	ConsoleQuestion4( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion4( );

public:
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

private:
	const int MONTH = 12;
	const int ARROW_DIR_LEFT  = -1;
	const int ARROW_DIR_RIGHT =  1;
	const int ERROR = 0xff;

private:
	CLICK_TARGET _click_target;
	int _selecting_num;
	unsigned char _select_month;
	unsigned char _select_day;
	ImagePtr _frame_image;
	ImagePtr _nums_image;
	ImagePtr _arrow_image;
	ImagePtr _monday_image;
};

