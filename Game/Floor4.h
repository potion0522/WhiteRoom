#pragma once
#include "Floor.h"
#include <vector>

/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	Floor4�̃��j�[�N�Ȃ��̂͂����ŊǗ�����

*******************************************************************/

PTR( Floor4 );
PTR( QuestionManager );
PTR( Question2FloorHint );
PTR( Question3FloorHint );
PTR( Sphere );

class Floor4 : public Floor {
public:
	Floor4( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager );
	virtual ~Floor4( );

public:
	void update( );
	void draw( ) const;

private:
	const FLOOR MY_FLOOR;

private:
	Question2FloorHintPtr _question2_hint;
	Question3FloorHintPtr _question3_hint;
	std::vector< SpherePtr > _dummy_spheres;
};
