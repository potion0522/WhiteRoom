#pragma once
#include "smart_ptr.h"

/***********************************************

Question5のフロア用ヒントを作成するクラス

***********************************************/

PTR( Question5FloorHint );
PTR( QuestionManager );
PTR( Model );

class Question5FloorHint {
public:
	Question5FloorHint( QuestionManagerConstPtr question_manager );
	virtual ~Question5FloorHint( );

public:
	void draw( ) const;

private:
	ModelPtr _frame_model;
	ModelPtr _nums_model;
};

