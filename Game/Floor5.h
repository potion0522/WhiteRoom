#pragma once
#include "Floor.h"

/*******************************************************************

	Floorの描画などを担当するFloorクラスを継承したクラス
	Floor5のユニークなものはここで管理する

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

