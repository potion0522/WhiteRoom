#pragma once
#include "smart_ptr.h"

PTR( Floor );
PTR( Model );

/*

	ŠK‘w’PˆÊ‚ÅŠÇ—‚·‚éƒNƒ‰ƒX
	•Ç‚È‚Ç‚Ìƒ|ƒŠƒSƒ“‚ğ©g‚Å•`‰æ

*/

class Floor {
public:
	Floor( double y );
	virtual ~Floor( );

public:
	double getY( ) const;

	void draw( ) const;

private:
	void generateRoom( );

private:
	double _y;

	ModelPtr _floor;
};

