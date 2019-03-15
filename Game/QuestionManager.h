#pragma once
#include "smart_ptr.h"

#include "define.h"
#include <array>

/********************************************************

–â‘è‚Ì“š‚¦‚ğŠÇ—‚·‚éƒNƒ‰ƒX

********************************************************/

PTR( QuestionManager );

class QuestionManager {
public:
	// 1.club 2.heart 3.diamont 4.spade
	static const int QUESTION_2_MAX_SUIT_NUM = 4;

private:
	struct Question1 {
		std::array< unsigned char, 3 > nums;
	};
	struct Question2 {
		unsigned char floor2_num;
		unsigned char floor3_num;
		unsigned char floor4_num;
	};
	struct Question3 {
		unsigned char floor1_num;
		unsigned char floor2_num;
		unsigned char floor4_num;
		char arrow_dir;
	};
	struct Question4 {
		unsigned char month;
		unsigned char day;
	};
	struct Question5 {
		std::array< unsigned char, 9 > num;
	};

public:
	QuestionManager( );
	virtual ~QuestionManager( );

public:
	// “š‚¦‡‚í‚¹
	bool answerQuestion1( unsigned char num1, unsigned char num2, unsigned char num3 ) const;
	bool answerQuestion2( unsigned char mark1, unsigned char mark2, unsigned char mark3 ) const;
	bool answerQuestion3( unsigned char num1, unsigned char num2, unsigned char num3 ) const;
	bool answerQuestion4( unsigned char month, unsigned char day ) const;
	bool answerQuestion5( unsigned char num1, unsigned char num2, unsigned char num3 ) const;

	// ƒqƒ“ƒg
	const std::array< unsigned char, 3 >& getHintQuestion1( ) const;
	const unsigned char getHintQuestion2( FLOOR floor ) const;
	const unsigned char getHintQuestion3( FLOOR floor ) const;
	const unsigned char getHintQuestion4Month( ) const;
	const unsigned char getHintQuestion4Day( ) const;
	const std::array< unsigned char, 9 >& getHintQuestion5( ) const;


private:
	void generateQuestion1( );
	void generateQuestion2( );
	void generateQuestion3( );
	void generateQuestion4( );
	void generateQuestion5( );

private:
	Question1 _question1;
	Question2 _question2;
	Question3 _question3;
	Question4 _question4;
	Question5 _question5;
};

