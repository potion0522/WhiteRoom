#pragma once
#include "Scene.h"
#include "smart_ptr.h"
#include "define.h"

/********************************************

タイトル画面の制御
エレベーターはFloor1,FloorGFを行ったり来たりしている。

********************************************/

PTR( SceneTitle );
PTR( Floor );
PTR( Elevator );
PTR( Image );

class SceneTitle : public Scene {
private:
	enum PHASE {
		PHASE_TITLE,
		PHASE_WHITEOUT
	};

public:
	SceneTitle( );
	virtual ~SceneTitle( );

public:
	void update( );
	void draw( ) const;

private:
	void actOnTitle( );
	void actOnWhiteOut( );
	void initializeCamera( );
	void updateMouse( );
	void updateStartButton( );
	void updateElevator( );
	int getNowCount( ) const;

private:
	const double FONT_FLASHING_RATIO = 720.0;
	const int    FONT_FLASHING_ALPHA = 150;
	const int    ELEVATOR_MOVE_TIME  = 5000;
	const int    WHITE_OUT_TIME      = 1500;

private:
	int _font_count;
	int _elevator_time;
	bool _elevator_count;
	int _white_out_start_time;
	FLOOR _elevator_floor;
	PHASE _phase;

	ImagePtr _logo;
	ImagePtr _click_to_start;
	ImagePtr _white_out;
	FloorPtr _floor;
	ElevatorPtr _elevator;
};

