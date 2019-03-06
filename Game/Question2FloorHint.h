#pragma once
#include "smart_ptr.h"
#include "define.h"

/***********************************************

Question2�̃t���A�p�q���g���쐬����N���X

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