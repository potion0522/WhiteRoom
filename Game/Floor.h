#pragma once
#include "smart_ptr.h"
#include "define.h"

#include <array>

PTR( Floor );
PTR( Model );
PTR( Wall );
PTR( CollideManager );
PTR( ElevatorAnnounceObservable );

/*

	�K�w�P�ʂŊǗ�����N���X
	�ǂȂǂ̃|���S�������g�ŕ`��

*/

class Floor {
public:
	Floor( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, FLOOR floor );
	virtual ~Floor( );

public:
	void update( );
	double getY( ) const;

	void draw( ) const;

private:
	void generateFloor( );
	void generateFloorCollider( );

	void setColliderToCollideManager( CollideManagerPtr collide_manager );

private:
	static const int NORMAL_WALL_NUM = 3;
	static const int ELEVATOR_SIDE_WALL_NUM = 2;

private:
	double _y;
	FLOOR _floor;

	ModelPtr _floor_model;
	std::array< WallPtr, NORMAL_WALL_NUM + ELEVATOR_SIDE_WALL_NUM > _wall_colliders;
	WallPtr _elevator_side_wall;
};

