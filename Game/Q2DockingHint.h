#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

PTR( Q2DockingHint );
PTR( Model );

class Q2DockingHint {
public:
	Q2DockingHint( const Vector& pos, const Matrix& rot );
	virtual ~Q2DockingHint( );

public:
	void draw( ) const;

private:
	Vector _pos;
	Matrix _rot;
	ModelPtr _model;
};

