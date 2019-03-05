#pragma once
#include "Floor.h"

/*******************************************************************

	Floorの描画などを担当するFloorクラスを継承したクラス
	Floor1のユニークなものはここで管理する

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

