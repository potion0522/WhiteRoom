#pragma once
#include "smart_ptr.h"
#include "define.h"

/***********************************************

Question2のフロア用ヒントを作成するクラス

***********************************************/


PTR( Model );
PTR( QuestionManager );

class Question2FloorHint {
public:
	Question2FloorHint( QuestionManagerConstPtr question_manager, FLOOR floor );
	virtual ~Question2FloorHint( );

public:
	void drawQuestion2Hint( ) const;

private:
	ModelPtr _hint;
};