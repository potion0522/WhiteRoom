#pragma once
#include "Floor.h"

/*******************************************************************

	Floorの描画などを担当するFloorクラスを継承したクラス
	Floor2のユニークなものはここで管理する

*******************************************************************/

PTR( Floor2 );
PTR( QuestionManager );
PTR( Question1FloorHint );
PTR( Question2FloorHint );

class Floor2 : public Floor {
public:
	Floor2( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, QuestionManagerConstPtr question_manager, FLOOR floor  );
	virtual ~Floor2( );

public:
	void update( );
	void draw( ) const;

private:
	Question1FloorHintPtr _question1_hint;
	Question2FloorHintPtr _question2_hint;
};

