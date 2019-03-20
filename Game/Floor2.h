#pragma once
#include "Floor.h"
#include <vector>

/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	Floor2�̃��j�[�N�Ȃ��̂͂����ŊǗ�����

*******************************************************************/

PTR( Floor2 );
PTR( QuestionManager );
PTR( Question1FloorHint );
PTR( Question2FloorHint );
PTR( Question3FloorHint );
PTR( Sphere );

class Floor2 : public Floor {
public:
	Floor2( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager );
	virtual ~Floor2( );

public:
	void update( );
	void draw( ) const;

private:
	const FLOOR MY_FLOOR;

private:
	Question1FloorHintPtr _question1_hint;
	Question2FloorHintPtr _question2_hint;
	Question3FloorHintPtr _question3_hint;
	std::vector< SpherePtr > _dummy_spheres;
};

