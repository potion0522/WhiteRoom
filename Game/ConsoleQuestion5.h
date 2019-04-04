#pragma once
#include "ConsoleQuestion.h"

#include <vector>

/*********************************************

ÉRÉìÉ\Å[ÉãÇÃ6PÇÃñ‚ëË(Question5)

*********************************************/

PTR( ConsoleQuestion5 );
PTR( Image );

class ConsoleQuestion5 : public ConsoleQuestion {
public:
	ConsoleQuestion5( std::function< void( ) > callback, QuestionManagerPtr question_manager );
	virtual ~ConsoleQuestion5( );

public:
	void draw( int x, int y ) const;

private:
	void actOnNone( );
	void actOnPush( );
	void actOnPushUp( );
	void actOnAnswer( );
	int getMouseOnNum( ) const;

private:
	const int ERROR = 0xff;

private:
	unsigned char _selecting_num;
	std::vector< unsigned char > _select_nums;
	ImagePtr _nums_image;
	ImagePtr _arrow_image;
	ImagePtr _frame_image;
};

