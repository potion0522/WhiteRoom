#pragma once
#include "ConsoleQuestion.h"

#include <vector>

/*********************************************

ÉRÉìÉ\Å[ÉãÇÃ5PÇÃñ‚ëË(Question3)

*********************************************/

PTR( ConsoleQuestion3 );
PTR( Image );

class ConsoleQuestion3 : public ConsoleQuestion {
public:
	ConsoleQuestion3( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion3( );

public:
	void draw( int x, int y ) const;

private:
	void actOnNone( );
	void actOnPush( );
	void actOnPushUp( );
	void actOnAnswer( );
	unsigned char getMouseOnNum( ) const;

private:
	static const int MAX_SELECT_NUM = 3;
	static const unsigned char ERROR_NUM = 0xff;

private:
	unsigned char _selecting_num;
	std::vector< unsigned char > _select_nums;
	ImagePtr _nums_image;
	ImagePtr _hint_image;
	ImagePtr _frame_image;
};

