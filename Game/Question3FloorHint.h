#pragma once
#include "smart_ptr.h"
#include "define.h"

/***********************************************

Question3のフロア用ヒントを作成するクラス

***********************************************/

PTR( Question3FloorHint );
PTR( QuestionManager );
PTR( Model );

class Question3FloorHint {
public:
	Question3FloorHint( QuestionManagerConstPtr question_manager, FLOOR floor );
	virtual ~Question3FloorHint( );

public:
	void draw( ) const;

private:
	ModelPtr _hint;
};

