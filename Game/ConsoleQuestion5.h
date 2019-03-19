#pragma once
#include "ConsoleQuestion.h"

/*********************************************

ÉRÉìÉ\Å[ÉãÇÃ6PÇÃñ‚ëË(Question5)

*********************************************/

PTR( ConsoleQuestion5 );
PTR( Image );

class ConsoleQuestion5 : public ConsoleQuestion {
public:
	ConsoleQuestion5( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion5( );

public:
	void update( );
	void draw( int x, int y ) const;
};

