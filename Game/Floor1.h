#pragma once
#include "Floor.h"

/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	Floor1�̃��j�[�N�Ȃ��̂͂����ŊǗ�����

*******************************************************************/

PTR( Floor1 );
PTR( QuestionManager );
PTR( Question3FloorHint );
PTR( Question5FloorHint );

class Floor1 : public Floor {
public:
	Floor1( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager );
	virtual ~Floor1( );

public:
	void draw( ) const;

private:
	const FLOOR MY_FLOOR;

private:
	Question3FloorHintPtr _question3_hint;
	Question5FloorHintPtr _question5_hint;
};

