#pragma once
#include "smart_ptr.h"

#include "define.h"
#include <array>

/********************************************************

問題の答えを管理するクラス
月, 日は1から値を保持

********************************************************/

PTR( QuestionManager );

class QuestionManager {
public:
	// 0.club 1.heart 2.diamond 3.spade 4.♪*3  5.♪*2  6.arrow*3  7.arrrow
	static const int QUESTION_2_MAX_MARK_NUM = 8;
	static const int QUESTION_5_MAX_NUM = 9; // 1 - 9

private:
	struct Question1 {
		std::array< unsigned char, 3 > nums;
	};
	struct Question2 {
		std::pair< unsigned char, unsigned char > floor2;
		std::pair< unsigned char, unsigned char > floor3;
		std::pair< unsigned char, unsigned char > floor4;
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
		std::array< unsigned char, QUESTION_5_MAX_NUM > nums;
	};

public:
	QuestionManager( );
	virtual ~QuestionManager( );

public:
	// 答え合わせ
	bool answerQuestion1( unsigned char num1, unsigned char num2, unsigned char num3 ) const;
	bool answerQuestion2( unsigned char red_mark, unsigned char green_mark, unsigned char blue_mark ) const;
	bool answerQuestion3( unsigned char num1, unsigned char num2, unsigned char num3 ) const;
	bool answerQuestion4( unsigned char month, unsigned char day ) const;
	bool answerQuestion5( unsigned char num1, unsigned char num2, unsigned char num3 ) const;

	// ヒント
	const std::array< unsigned char, 3 >& getHintQuestion1( ) const;
	const unsigned char getHintQuestion2Mark( FLOOR floor ) const;
	const unsigned char getHintQuestion2Color( FLOOR floor ) const;
	const unsigned char getHintQuestion3( FLOOR floor ) const;
	const char getHintQuestion3Arrow( ) const;
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

