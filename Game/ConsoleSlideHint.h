#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

PTR( ConsoleSlideHint );
PTR( Model );

class ConsoleSlideHint {
public:
	ConsoleSlideHint( const Vector& pos, Matrix& rot );
	virtual ~ConsoleSlideHint( );

public:
	void draw( ) const;

private:
	Vector _pos;
	Matrix _rot;
	ModelPtr _model;
};

