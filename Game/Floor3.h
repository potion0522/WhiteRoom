#pragma once
#include "Floor.h"
#include <vector>

/*******************************************************************

	Floor�̕`��Ȃǂ�S������Floor�N���X���p�������N���X
	Floor3�̃��j�[�N�Ȃ��̂͂����ŊǗ�����

*******************************************************************/

PTR( Floor3 );
PTR( QuestionManager );
PTR( Question2FloorHint );
PTR( Sphere );

class Floor3 : public Floor {
public:
	Floor3( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor  );
	virtual ~Floor3( );

public:
	void update( );
	void draw( ) const;

private:
	Question2FloorHintPtr _question2_hint;
	std::vector< SpherePtr > _dummy_spheres;
};

