#pragma once
#include "smart_ptr.h"

PTR( Floor );
PTR( Model );

/*

	階層単位で管理するクラス
	壁などのポリゴンを自身で描画

*/

class Floor {
public:
	Floor( double y );
	virtual ~Floor( );

public:
	double getY( ) const;

	void draw( ) const;

private:
	void generateFloor( );

private:
	double _y;

	ModelPtr _floor;
};

