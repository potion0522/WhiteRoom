#include "QuestionManager.h"

#include "Random.h"

#include <unordered_map>
#include <vector>

QuestionManager::QuestionManager( ) {
	generateQuestion1( );
	generateQuestion2( );
	generateQuestion3( );
	generateQuestion4( );
	generateQuestion5( );
}

QuestionManager::~QuestionManager( ) {
}

bool QuestionManager::answerQuestion1( unsigned char num1, unsigned char num2, unsigned char num3 ) const {
	for ( int i = 0; i < 3; i++ ) {
		if ( num1 != _question1.nums[ i ] && num2 != _question1.nums[ i ] && num3 != _question1.nums[ i ] ) {
			return false;
		}
	}
	return true;
}

bool QuestionManager::answerQuestion2( unsigned char mark1, unsigned char mark2, unsigned char mark3 ) const {
	if ( mark1 == _question2.floor2_num &&
	     mark2 == _question2.floor3_num &&
	     mark3 == _question2.floor4_num ) {
		return true;
	}
	return false;
}

bool QuestionManager::answerQuestion3( unsigned char num1, unsigned char num2, unsigned char num3 ) const {
	bool result = false;

	// ‰ºŠK‘w‚©‚çãŠK‘w
	if ( _question3.arrow_dir > 0 ) {
		if ( num1 == _question3.floor4_num &&
			 num2 == _question3.floor2_num &&
			 num3 == _question3.floor1_num ) {
			result = true;
		}
	} else {
	// ãŠK‘w‚©‚ç‰ºŠK‘w
		if ( num1 == _question3.floor1_num &&
			 num2 == _question3.floor2_num &&
			 num3 == _question3.floor4_num ) {
			result = true;
		}
	}

	return false;
}

bool QuestionManager::answerQuestion4( unsigned char month, unsigned char day ) const {
	return false;
}

bool QuestionManager::answerQuestion5( unsigned char num1, unsigned char num2, unsigned char num3 ) const {
	return false;
}

const std::array< unsigned char, 3 >& QuestionManager::getHintQuestion1( ) const {
	return _question1.nums;
}

const unsigned char QuestionManager::getHintQuestion2( FLOOR floor ) const {
	if ( floor == FLOOR_2 ) {
		return _question2.floor2_num;
	}
	if ( floor == FLOOR_3 ) {
		return _question2.floor3_num;
	}
	if ( floor == FLOOR_4 ) {
		return _question2.floor4_num;
	}

	// ƒGƒ‰[
	return 0xff;
}

const unsigned char QuestionManager::getHintQuestion3( FLOOR floor ) const {
	if ( floor == FLOOR_1 ) {
		return _question3.floor1_num;
	}
	if ( floor == FLOOR_2 ) {
		return _question3.floor2_num;
	}
	if ( floor == FLOOR_4 ) {
		return _question3.floor4_num;
	}

	// ƒGƒ‰[
	return 0xff;
}

const unsigned char QuestionManager::getHintQuestion4Month( ) const {
	return _question4.month;
}

const unsigned char QuestionManager::getHintQuestion4Day( ) const {
	return _question4.day;
}

const std::array< unsigned char, 9 >& QuestionManager::getHintQuestion5( ) const {
	return _question5.num;
}

void QuestionManager::generateQuestion1( ) {
	const int MAX_IDX = 10;
	std::unordered_map< unsigned char, unsigned char > nums;
	for ( int i = 0; i < MAX_IDX; i++ ) {
		nums[ i ] = i;
	}

	std::vector< unsigned char > select_nums;
	RandomPtr random = Random::getTask( );
	// 3ŒÂ‘Io‚·‚é‚Ü‚Åƒ‹[ƒv
	while ( nums.size( ) > MAX_IDX - 3 ) {
		int idx = random->getRand( ) % MAX_IDX;
		if ( nums.count( idx ) == 0 ) {
			continue;
		}

		select_nums.push_back( nums[ idx ] );
		nums.erase( idx );
	}

	// ‘Io‚µ‚½’l‚ğ‘ã“ü
	for ( int i = 0; i < 3; i++ ) {
		_question1.nums[ i ] = select_nums[ i ];
	}
}

void QuestionManager::generateQuestion2( ) {
	const int MAX_IDX = 3;
	std::vector< unsigned char > nums;
	RandomPtr random = Random::getTask( );

	while ( nums.size( ) < 3 ) {
		int num = random->getRand( ) % QUESTION_2_MAX_MARK_NUM;
		
		bool insert = true;
		for ( int i = 0; i < nums.size( ); i++ ) {
			if ( num == nums[ i ] ) {
				insert = false;
				break;
			}
		}

		if ( insert ) {
			nums.push_back( num );
		}
	}

	_question2.floor2_num = nums[ 0 ];
	_question2.floor3_num = nums[ 1 ];
	_question2.floor4_num = nums[ 2 ];
}

void QuestionManager::generateQuestion3( ) {
	const int MAX_IDX = 3;
	const int MAX_ANSWER_NUM = 9;
	std::vector< unsigned char > nums;
	RandomPtr random = Random::getTask( );

	while ( nums.size( ) < 3 ) {
		int num = random->getRand( ) % MAX_ANSWER_NUM;
		
		bool insert = true;
		for ( int i = 0; i < nums.size( ); i++ ) {
			if ( num == nums[ i ] ) {
				insert = false;
				break;
			}
		}

		if ( insert ) {
			nums.push_back( num );
		}
	}

	_question3.floor1_num = nums[ 0 ];
	_question3.floor2_num = nums[ 1 ];
	_question3.floor4_num = nums[ 2 ];
	_question3.arrow_dir = ( random->getRand( 0, 1 ) == 0 ? -1 : 1 );
}

void QuestionManager::generateQuestion4( ) {
}

void QuestionManager::generateQuestion5( ) {
}
