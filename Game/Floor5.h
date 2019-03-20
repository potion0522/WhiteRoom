#pragma once
#include "Floor.h"

/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	Floor5�̃��j�[�N�Ȃ��̂͂����ŊǗ�����

*******************************************************************/

PTR( Floor5 );
PTR( QuestionManager );
PTR( Question5FloorHint );
PTR( Sphere );

class Floor5 : public Floor {
public:
	Floor5( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager );
	virtual ~Floor5( );

public:
	void draw( ) const;

private:
	const FLOOR MY_FLOOR;

private:
	Question5FloorHintPtr _question5_hint;
};

