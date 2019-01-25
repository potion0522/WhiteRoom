#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

PTR( Elevator );
PTR( Model );

class Elevator {
public:
	Elevator( const Vector& init_pos );
	virtual ~Elevator( );

public:
	void update( );
	void setMoveOrder( int order_floor );
	void draw( ) const;

private:
	void generateElevator( );
	void move( );

public:
	bool isMoving( ) const;

private:
	Vector _pos;
	unsigned char _past_floor;
	unsigned char _floor;
	unsigned int _starting_time;
	bool _moving;

	ModelPtr _model;
};

