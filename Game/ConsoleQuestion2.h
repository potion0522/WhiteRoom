#pragma once
#include "ConsoleQuestion.h"

#include <array>

/*********************************************

コンソールの1Pの問題(Question2)

*********************************************/

PTR( ConsoleQuestion2 );
PTR( Image );

class ConsoleQuestion2 : public ConsoleQuestion {
private:
	enum STATE {
		STATE_NONE,
		STATE_PUSH,
		STATE_PUSH_UP,
		STATE_ANSWER
	};

public:
	ConsoleQuestion2( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion2( );

public:
	void update( );
	void draw( int x, int y ) const;

private:
	void actOnNone( );
	void actOnPush( );
	void actOnPushUp( );
	void actOnAnswer( );
	bool isMouseOnButton( ) const;

private:
	static const int ANSWER_NUM = 3;

private:
	STATE _state;
	std::array< unsigned char, ANSWER_NUM > _mark_state;
	ImagePtr _mark_image;
};

