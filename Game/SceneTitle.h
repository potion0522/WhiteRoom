#pragma once
#include "Scene.h"
#include "smart_ptr.h"
#include "define.h"

/********************************************

�^�C�g����ʂ̐���
�G���x�[�^�[��Floor1,FloorGF���s�����藈���肵�Ă���B

********************************************/

PTR( SceneTitle );
PTR( Floor );
PTR( Elevator );
PTR( Image );

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );

public:
	void update( );
	void draw( ) const;

private:
	void initializeCamera( );
	void updateMouse( );
	void updateStartButton( );
	void updateElevator( );
	int getNowCount( ) const;

private:
	const double FONT_FLASHING_RATIO;
	const int FONT_FLASHING_ALPHA;
	const int ELEVATOR_MOVE_TIME;

private:
	int _font_count;
	int _elevator_time;
	bool _elevator_count;
	FLOOR _elevator_floor;

	ImagePtr _logo;
	ImagePtr _click_to_start;
	FloorPtr _floor;
	ElevatorPtr _elevator;
};

