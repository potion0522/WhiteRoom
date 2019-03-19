#pragma once
#include "smart_ptr.h"
#include "define.h"
#include "Mathematics.h"

/***********************************************

Question4のフロア用ヒントを作成するクラス

***********************************************/

PTR( Question4FloorHint );
PTR( QuestionManager );
PTR( Model );

class Question4FloorHint {
public:
	Question4FloorHint( QuestionManagerConstPtr question_manager );
	virtual ~Question4FloorHint( );

public:
	void draw( ) const;

private:
	const float MONTH = 12.0f;
	const int OFFSET_Y = -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * FLOOR_3 + FLOOR_HEIGHT - 10;

private:
	Vector _month_pos;
	Vector _day_pos;
	ModelPtr _month_hint_model;
	ModelPtr _iteration_model;
	ModelPtr _week_model;
};

