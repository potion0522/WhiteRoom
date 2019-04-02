#pragma once
#include "Floor.h"
#include <vector>

/*******************************************************************

	Floorの描画などを担当するFloorクラスを継承したクラス
	Floor3のユニークなものはここで管理する

*******************************************************************/

PTR( Floor3 );
PTR( QuestionManager );
PTR( Question2FloorHint );
PTR( Question4FloorHint );
PTR( Question5FloorHint );
PTR( DummySphere );

class Floor3 : public Floor {
public:
	Floor3( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager );
	virtual ~Floor3( );

public:
	void update( );
	void draw( ) const;

private:
	const FLOOR MY_FLOOR;

private:
	Question2FloorHintPtr _question2_hint;
	Question4FloorHintPtr _question4_hint;
	Question5FloorHintPtr _question5_hint;
	std::vector< DummySpherePtr > _dummy_spheres;
};

