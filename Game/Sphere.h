#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

/**************************************************

���̂��̂��̂̃N���X

**************************************************/


PTR( Model );

class Sphere {
public:
	Sphere( Vector pos, double radius );
	virtual ~Sphere( );

public:
	void draw( ) const;

private:
	void generate( );

private:
	static const int _DIV_NUM = 30;

protected:
	ModelPtr _model;
	Vector _pos;
	double _radius;
};

