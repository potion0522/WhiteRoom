#pragma once
#include "ConsoleQuestion.h"

PTR( ConsoleQuestion1 );

class ConsoleQuestion1 : public ConsoleQuestion {
public:
	ConsoleQuestion1( const int& x, const int& y, std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion1( );

public:
	void update( );
	void draw( ) const;
};

