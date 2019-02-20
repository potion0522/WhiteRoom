#pragma once
#include "smart_ptr.h"

#include <array>

PTR( Floor );
PTR( Model );
PTR( Wall );
PTR( CollideManager );

/*

	ŠK‘w’PˆÊ‚ÅŠÇ—‚·‚éƒNƒ‰ƒX
	•Ç‚È‚Ç‚Ìƒ|ƒŠƒSƒ“‚ğ©g‚Å•`‰æ

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
	static const int WALL_NUM = 5;

private:
	double _y;

	ModelPtr _floor;
	std::array< WallPtr, WALL_NUM > _wall_colliders;
};

