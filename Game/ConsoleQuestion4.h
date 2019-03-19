#pragma once
#include "ConsoleQuestion.h"


/*********************************************

�R���\�[����4P�̖��(Question4)

*********************************************/

PTR( ConsoleQuestion4 );
PTR( Image );

class ConsoleQuestion4 : public ConsoleQuestion {
public:
	ConsoleQuestion4( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion4( );

public:
	void update( );
	void draw( int x, int y ) const;
};

