#pragma once
#include "Floor.h"

/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	Floor1�̃��j�[�N�Ȃ��̂͂����ŊǗ�����

*******************************************************************/

PTR( Floor1 );
PTR( QuestionManager );

class Floor1 : public Floor {
public:
	Floor1( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor  );
	virtual ~Floor1( );

public:
	void draw( ) const;
};

