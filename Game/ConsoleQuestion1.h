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
	void update( );
	void draw( int x, int y ) const;

private:
	bool updateState( );
	void checkAnswer( );
	bool isClicked( ) const;
	int getClickIdx( ) const;

private:
	static const int _SQUARE_NUM = 9;
	static const unsigned int _BLACK = 1;
	static const unsigned int _WHITE = 0;

private:
	ImagePtr _square;
	std::array< unsigned char, _SQUARE_NUM > _square_state;
	int _square_width;
};

