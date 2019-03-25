#pragma once;
#include "ConsoleQuestion.h"
#include <array>

/*********************************************

ÉRÉìÉ\Å[ÉãÇÃ3PÇÃñ‚ëË(Question1)

*********************************************/

PTR( ConsoleQuestion1 );
PTR( Image );

class ConsoleQuestion1 : public ConsoleQuestion {
public:
	ConsoleQuestion1( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion1( );

public:
	void draw( int x, int y ) const;

private:
	void actOnNone( );
	void actOnPush( );
	void actOnPushUp( );
	void actOnAnswer( );
	int getMouseOnSquareIdx( ) const;
	int getBlackSquareNum( ) const;

private:
	static const int _SQUARE_NUM = 9;
	const unsigned int BLACK = 1;
	const unsigned int WHITE = 0;
	const unsigned int ERROR = 0xff;

private:
	int _selecting_idx;
	int _square_width;
	int _square_height;
	std::array< unsigned char, _SQUARE_NUM > _square_state;
	ImagePtr _square;
};

