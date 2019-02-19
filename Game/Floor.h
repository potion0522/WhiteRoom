#pragma once
#include "smart_ptr.h"

#include <array>

PTR( Floor );
PTR( Model );
PTR( Wall );
PTR( CollideManager );

/*

	階層単位で管理するクラス
	壁などのポリゴンを自身で描画

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

private:
	double _y;

	ModelPtr _floor;
	std::array< WallPtr, 4 > _wall_colliders;
};

