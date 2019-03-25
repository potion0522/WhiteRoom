#pragma once
#include "smart_ptr.h"
#include "define.h"

/***********************************************

Question5�̃t���A�p�q���g���쐬����N���X

***********************************************/

PTR( Question5FloorHint );
PTR( QuestionManager );
PTR( Model );

class Question5FloorHint {
public:
	Question5FloorHint( QuestionManagerConstPtr question_manager, FLOOR floor );
	virtual ~Question5FloorHint( );

public:
	void draw( ) const;

private:
	ModelPtr _frame_model;
	ModelPtr _nums_model;
	ModelPtr _floor_num_model;
};

