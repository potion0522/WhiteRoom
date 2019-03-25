#pragma once
#include "smart_ptr.h"
#include "define.h"

#include <array>

/*************************************

	�K�w�P�ʂŊǗ�����N���X
	�ǂȂǂ̃|���S�������g�ŕ`��

*************************************/

PTR( Model );
PTR( Wall );
PTR( CollideManager );
PTR( ElevatorAnnounceObservable );


class Floor {
public:
	Floor( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, FLOOR floor );
	virtual ~Floor( );

public:
	virtual void update( ) { };
	virtual void draw( ) const;

protected:
	void drawFloor( ) const;

private:
	void generateFloor( );
	void generateFloorCollider( );

	void setColliderToCollideManager( CollideManagerPtr collide_manager );

private:
	static const int NORMAL_WALL_NUM = 3;
	static const int ELEVATOR_SIDE_WALL_NUM = 2;

protected:
	double _y;
	FLOOR _floor;

private:
	ModelPtr _floor_model;
	ModelPtr _wall_model;
	std::array< WallPtr, NORMAL_WALL_NUM + ELEVATOR_SIDE_WALL_NUM > _wall_colliders;
	WallPtr _elevator_side_wall;
};

