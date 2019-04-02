#include "QuestionManager.h"
#include "Debug.h"

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

bool QuestionManager::answerQuestion2( unsigned char red_mark, unsigned char green_mark, unsigned char blue_mark ) const {
	const int MAX_COLOR = 3;
	std::array< unsigned char, MAX_COLOR > answer;
	for ( int i = 0; i < MAX_COLOR; i++ ) {
		int mark;
		int color_idx = i + 1;

		if ( _question2.floor2.first == color_idx ) {
			mark = _question2.floor2.second;
		}
		if ( _question2.floor3.first == color_idx ) {
			mark = _question2.floor3.second;
		}
		if ( _question2.floor4.first == color_idx ) {
			mark = _question2.floor4.second;
		}

		answer[ i ] = mark;
	}

	if ( answer[ 0 ] == red_mark &&
		 answer[ 1 ] == green_mark &&
		 answer[ 2 ] == blue_mark ) {
		return true;
	}

	return false;
}

bool QuestionManager::answerQuestion3( unsigned char num1, unsigned char num2, unsigned char num3 ) const {
	bool result = false;

	// 下階層から上階層
	if ( _question3.arrow_dir > 0 ) {
		if ( num1 == _question3.floor4_num &&
			 num2 == _question3.floor2_num &&
			 num3 == _question3.floor1_num ) {
			result = true;
		}
	} else {
	// 上階層から下階層
		if ( num1 == _question3.floor1_num &&
			 num2 == _question3.floor2_num &&
			 num3 == _question3.floor4_num ) {
			result = true;
		}
	}

	return result;
}

bool QuestionManager::answerQuestion4( unsigned char month, unsigned char day ) const {
	if ( _question4.month == month && _question4.day == day ) {
		return true;
	}
	return false;
}

bool QuestionManager::answerQuestion5( unsigned char num1, unsigned char num2, unsigned char num3 ) const {
	std::array< unsigned char, 3 > answer = {
		_question5.nums[ _question1.nums[ 0 ] ],	
		_question5.nums[ _question1.nums[ 1 ] ],	
		_question5.nums[ _question1.nums[ 2 ] ],	
	};

	// ソート
	const int MAX = 3;
	for ( int i = 0; i < MAX; i++ ) {
		for ( int j = 0; j < MAX - i - 1; j++ ) {
			int a = answer[ j ];
			int b = answer[ j + 1 ];
			if ( a > b ) {
				answer[ j ] = b;
				answer[ j + 1 ] = a;
			}
		}
	}

	if ( num1 == answer[ 0 ] &&
		 num2 == answer[ 1 ] &&
		 num3 == answer[ 2 ] ) {
		return true;
	}
	return false;
}

const std::array< unsigned char, 3 >& QuestionManager::getHintQuestion1( ) const {
	return _question1.nums;
}

const unsigned char QuestionManager::getHintQuestion2Mark( FLOOR floor ) const {
	if ( floor == FLOOR_2 ) {
		return _question2.floor2.second;
	}
	if ( floor == FLOOR_3 ) {
		return _question2.floor3.second;
	}
	if ( floor == FLOOR_4 ) {
		return _question2.floor4.second;
	}

	// エラー
	return 0xff;
}

const unsigned char QuestionManager::getHintQuestion2Color( FLOOR floor ) const {
	if ( floor == FLOOR_2 ) {
		return _question2.floor2.first;
	}
	if ( floor == FLOOR_3 ) {
		return _question2.floor3.first;
	}
	if ( floor == FLOOR_4 ) {
		return _question2.floor4.first;
	}

	// エラー
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

	// エラー
	return 0xff;
}

const char QuestionManager::getHintQuestion3Arrow( ) const {
	return _question3.arrow_dir;
}

const unsigned char QuestionManager::getHintQuestion4Month( ) const {
	return _question4.month;
}

const unsigned char QuestionManager::getHintQuestion4Day( ) const {
	return _question4.day;
}

const std::array< unsigned char, 9 >& QuestionManager::getHintQuestion5( ) const {
	return _question5.nums;
}

void QuestionManager::generateQuestion1( ) {
	const int MAX_IDX = 9;
	std::unordered_map< unsigned char, unsigned char > nums;
	for ( int i = 0; i < MAX_IDX; i++ ) {
		nums[ i ] = i;
	}

	std::vector< unsigned char > select_nums;
	RandomPtr random = Random::getTask( );
	// 3個選出するまでループ
	while ( nums.size( ) > MAX_IDX - 3 ) {
		int idx = random->getRand( 0, MAX_IDX );
		if ( nums.count( idx ) == 0 ) {
			continue;
		}

		select_nums.push_back( nums[ idx ] );
		nums.erase( idx );
	}

	// 選出した値を代入
	for ( int i = 0; i < 3; i++ ) {
		_question1.nums[ i ] = select_nums[ i ];
	}

	// debug
	Debug* debug = Debug::getInstance( );
	std::string message = "Question1 : ";
	message += std::to_string( _question1.nums[ 0 ] );
	message += ",";
	message += std::to_string( _question1.nums[ 1 ] );
	message += ",";
	message += std::to_string( _question1.nums[ 2 ] );
	debug->addSaveMessage( message.c_str( ) );
}

void QuestionManager::generateQuestion2( ) {
	const int MAX_IDX = 3;
	const int MAX_COLOR = 3;
	std::vector< std::pair< unsigned char, unsigned char > > nums;
	RandomPtr random = Random::getTask( );

	while ( nums.size( ) < MAX_IDX ) {
		// 色
		int color = random->getRand( 0x01, MAX_COLOR );
		// マーク
		int num = random->getRand( 0, QUESTION_2_MAX_MARK_NUM - 1 );
		
		// 選択された色とマークがなければ追加
		bool insert = true;
		for ( int i = 0; i < nums.size( ); i++ ) {
			if ( color == nums[ i ].first || num == nums[ i ].second ) {
				insert = false;
				break;
			}
		}

		if ( insert ) {
			nums.push_back( std::pair< unsigned char, unsigned char >( color, num ) );
		}
	}

	_question2.floor2 = nums[ 0 ];
	_question2.floor3 = nums[ 1 ];
	_question2.floor4 = nums[ 2 ];

	// debug
	Debug* debug = Debug::getInstance( );
	std::string message = "Question2 : ";
	message += std::to_string( _question2.floor2.second );
	message += ",";
	message += std::to_string( _question2.floor3.second );
	message += ",";
	message += std::to_string( _question2.floor4.second );
	debug->addSaveMessage( message.c_str( ) );
}

void QuestionManager::generateQuestion3( ) {
	const int MAX_IDX = 3;
	const int MAX_ANSWER_NUM = 9;
	std::vector< unsigned char > nums;
	RandomPtr random = Random::getTask( );

	while ( nums.size( ) < MAX_IDX ) {
		int num = random->getRand( 0, MAX_ANSWER_NUM );
		
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
	
	// debug
	Debug* debug = Debug::getInstance( );
	std::string message = "Question3 : ";
	message += std::to_string( _question3.floor1_num );
	message += ",";
	message += std::to_string( _question3.floor2_num );
	message += ",";
	message += std::to_string( _question3.floor4_num );
	debug->addSaveMessage( message.c_str( ) );
}

void QuestionManager::generateQuestion4( ) {
	RandomPtr random = Random::getTask( );
	_question4.month = ( unsigned char )random->getRand( 1, 12 );
	_question4.day   = ( unsigned char )random->getRand( 1, DAY_IN_MONTH[ _question4.month - 1 ] );

	// debug
	Debug* debug = Debug::getInstance( );
	std::string message = "Question4 : ";
	message += std::to_string( _question4.month );
	message += ",";
	message += std::to_string( _question4.day );
	debug->addSaveMessage( message.c_str( ) );
}

void QuestionManager::generateQuestion5( ) {

	// 要素を用意しておく
	std::unordered_map< unsigned char, unsigned char > nums;
	for ( int i = 0; i < QUESTION_5_MAX_NUM; i++ ) {
		nums[ i + 1 ] = i + 1;
	}

	// ランダムで要素番号を選択し、抜いていく
	RandomPtr random = Random::getTask( );
	while ( nums.size( ) > 0 ) {
		int idx = random->getRand( 1, ( long )nums.size( ) );

		// イテレーターで番号まで回す
		std::unordered_map< unsigned char, unsigned char >::iterator ite;
		ite = nums.begin( );
		for ( int i = 0; i < idx - 1; i++ ) {
			ite++;
		}

		_question5.nums[ QUESTION_5_MAX_NUM - ( int )nums.size( ) ] = ite->second;
		nums.erase( ite );
	}
	
	// debug
	std::array< unsigned char, 3 > answer = {
		_question5.nums[ _question1.nums[ 0 ] ],	
		_question5.nums[ _question1.nums[ 1 ] ],	
		_question5.nums[ _question1.nums[ 2 ] ],	
	};

	Debug* debug = Debug::getInstance( );
	std::string message = "Question5 : ";
	message += std::to_string( answer[ 0 ] );
	message += ",";
	message += std::to_string( answer[ 1 ] );
	message += ",";
	message += std::to_string( answer[ 2 ] );
	debug->addSaveMessage( message.c_str( ) );
}
