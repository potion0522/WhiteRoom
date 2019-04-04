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
	ConsoleQuestion( std::function< void( ) > callback, QuestionManagerPtr question_manager, int my_question_num );
	virtual ~ConsoleQuestion( );

public:
	void update( );
	virtual void draw( int x, int y ) const = 0;
	void refresh( );

protected:
	virtual void actOnNone( ) = 0;
	virtual void actOnPush( ) = 0;
	virtual void actOnPushUp( ) = 0;
	virtual void actOnAnswer( ) = 0;
	int getNowCount( ) const;
	void playUnClearSE( );
	void playClearSE( );
	void clear( );

protected:
	static const int ANSWER_WAIT_TIME = 750; // ミリ
	const int MY_QUESTION_NUM;

protected:
	QuestionManagerPtr  _question_manager;
	STATE _state;
	int _start_time;
};

