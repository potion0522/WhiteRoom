#pragma once
#include "smart_ptr.h"

PTR( Room );
PTR( Model );

class Room {
public:
	Room( double y );
	virtual ~Room( );

public:
	double getY( ) const;

	void draw( ) const;

private:
	double _y;

	ModelPtr _room;
};

