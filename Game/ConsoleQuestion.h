#pragma once
#include "PageContent.h"
#include "smart_ptr.h"

/************************************************

コンソールの問題解答欄のベースクラス

************************************************/

PTR( QuestionManager );

class ConsoleQuestion : public PageContent {
protected:
	enum STATE {
		STATE_NONE,
		STATE_PUSH,
		STATE_PUSH_UP,
		STATE_ANSWER
	};

public:
	ConsoleQuestion( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion( );

public:
	void update( );
	virtual void draw( int x, int y ) const = 0;

protected:
	virtual void actOnNone( ) = 0;
	virtual void actOnPush( ) = 0;
	virtual void actOnPushUp( ) = 0;
	virtual void actOnAnswer( ) = 0;
	int getNowCount( ) const;

protected:
	static const int ANSWER_WAIT_TIME = 2000; // ミリ

protected:
	QuestionManagerConstPtr  _question_manager;
	STATE _state;
	int _start_time;
};

