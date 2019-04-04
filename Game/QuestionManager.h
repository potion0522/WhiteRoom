#pragma once
#include "smart_ptr.h"

#include "define.h"
#include <array>
#include <vector>

/********************************************************

���̓������Ǘ�����N���X
��, ����1����l��ێ�

********************************************************/

PTR( QuestionManager );

class QuestionManager {
public:
	// 0.club 1.heart 2.diamond 3.spade 4.��*3  5.��*2  6.arrow*3  7.arrrow
	static const int QUESTION_2_MAX_MARK_NUM = 8;
	static const int QUESTION_5_MAX_NUM = 9; // 1 - 9

private:
	struct Question {
		bool clear;
		unsigned char priority; // �Ⴂ���̂قǗD�悪����
		unsigned char question_num;

		Question( ) :
		clear( false ),
		priority( 99 ),
		question_num( 0 ) {
		}

		Question( unsigned char in_priority, unsigned char in_question_num ) :
		clear( false ),
		priority( in_priority ),
		question_num( in_question_num ) {
		}
	};
	struct Question1 : public Question {
		Question1( ) :
		Question( 1, 1 ) {
		}
		std::array< unsigned char, 3 > nums;
	};
	struct Question2 : public Question {
		Question2( ) :
		Question( 3, 2 ) {
		}
		std::pair< unsigned char, unsigned char > floor2;
		std::pair< unsigned char, unsigned char > floor3;
		std::pair< unsigned char, unsigned char > floor4;
	};
	struct Question3 : public Question {
		Question3( ) :
		Question( 4, 3 ) {
		}
		unsigned char floor1_num;
		unsigned char floor2_num;
		unsigned char floor4_num;
		char arrow_dir;
	};
	struct Question4 : public Question {
		Question4( ) :
		Question( 2, 4 ) {
		}
		unsigned char month;
		unsigned char day;
	};
	struct Question5 : public Question {
		Question5( ) :
		Question( 5, 5 ) {
		}
		std::array< unsigned char, QUESTION_5_MAX_NUM > nums;
	};

public:
	QuestionManager( );
	virtual ~QuestionManager( );

public:
	// �������킹
	bool answerQuestion1( unsigned char num1, unsigned char num2, unsigned char num3 ) const;
	bool answerQuestion2( unsigned char red_mark, unsigned char green_mark, unsigned char blue_mark ) const;
	bool answerQuestion3( unsigned char num1, unsigned char num2, unsigned char num3 ) const;
	bool answerQuestion4( unsigned char month, unsigned char day ) const;
	bool answerQuestion5( unsigned char num1, unsigned char num2, unsigned char num3 ) const;

	void clearQuestion( int question_num );

	// �q���g
	const std::array< unsigned char, 3 >& getHintQuestion1( ) const;
	const unsigned char getHintQuestion2Mark( FLOOR floor ) const;
	const unsigned char getHintQuestion2Color( FLOOR floor ) const;
	const unsigned char getHintQuestion3( FLOOR floor ) const;
	const char getHintQuestion3Arrow( ) const;
	const unsigned char getHintQuestion4Month( ) const;
	const unsigned char getHintQuestion4Day( ) const;
	const std::array< unsigned char, 9 >& getHintQuestion5( ) const;
	int getHintOpenTime( ) const;
	int getHintQuestionNum( ) const;


private:
	void generateQuestion1( );
	void generateQuestion2( );
	void generateQuestion3( );
	void generateQuestion4( );
	void generateQuestion5( );
	void updateHintQuestion( );

private:
	Question1 _question1;
	Question2 _question2;
	Question3 _question3;
	Question4 _question4;
	Question5 _question5;
	std::vector< Question > _clear_state;
	unsigned char _now_hint_question_num;
	int _hint_open_time;
};

