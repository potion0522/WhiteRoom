#pragma once
#include "Floor.h"

/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	Floor2�̃��j�[�N�Ȃ��̂͂����ŊǗ�����

*******************************************************************/

PTR( Floor2 );
PTR( QuestionManager );
PTR( Question1FloorHint );
PTR( Question2FloorHint );

class Floor2 : public Floor {
public:
	Floor2( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor  );
	virtual ~Floor2( );

public:
	void update( );
	void draw( ) const;

private:
	Question1FloorHintPtr _question1_hint;
	Question2FloorHintPtr _question2_hint;
};

