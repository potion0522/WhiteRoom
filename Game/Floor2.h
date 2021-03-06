#pragma once
#include "Floor.h"
#include <vector>

/*******************************************************************

	Floorの描画などを担当するFloorクラスを継承したクラス
	Floor2のユニークなものはここで管理する

*******************************************************************/

PTR( Floor2 );
PTR( QuestionManager );
PTR( Question1FloorHint );
PTR( Question2FloorHint );
PTR( Question3FloorHint );
PTR( Question5FloorHint );
PTR( ConsoleSlideHint );
PTR( DummySphere );

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
	Question5FloorHintPtr _question5_hint;
	ConsoleSlideHintPtr _console_slide_hint;
	std::vector< DummySpherePtr > _dummy_spheres;
};

