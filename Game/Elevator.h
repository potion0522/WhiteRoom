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
	void draw( ) const;

private:
	void generateElevator( );

private:
	Vector _pos;

	ModelPtr _model;
};

