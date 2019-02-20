#pragma once
#include "smart_ptr.h"

#include <array>

PTR( Floor );
PTR( Model );
PTR( Wall );
PTR( CollideManager );

/*

	�K�w�P�ʂŊǗ�����N���X
	�ǂȂǂ̃|���S�������g�ŕ`��

*/

class Floor {
public:
	Floor( CollideManagerPtr collide_manager, double y );
	virtual ~Floor( );

public:
	double getY( ) const;

	void draw( ) const;

private:
	void generateFloor( );
	void generateFloorCollider( );

	void setColliderToCollideManager( CollideManagerPtr collide_manager );

private:
	static const int NORMAL_WALL_NUM = 3;
	static const int ELEVATOR_SIDE_WALL_NUM = 3;

private:
	double _y;

	ModelPtr _floor;
	std::array< WallPtr, NORMAL_WALL_NUM + ELEVATOR_SIDE_WALL_NUM > _wall_colliders;
};

