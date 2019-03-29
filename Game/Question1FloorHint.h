#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

/***********************************************

Question1のフロア用ヒントを作成するクラス

***********************************************/


PTR( Model );
PTR( QuestionManager );

class Question1FloorHint {
public:
	Question1FloorHint( QuestionManagerConstPtr question_manager );
	virtual ~Question1FloorHint( );

public:
	void draw( ) const;

private:
	ModelPtr _hint;
};

