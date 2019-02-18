#pragma once
#include "SquareCollider.h"
#include "smart_ptr.h"

PTR( TestSquare );
PTR( Model );

class TestSquare : public SquareCollider {
public:
	TestSquare( );
	virtual ~TestSquare( );

public:
	void draw( ) const;
	void onColliderEnter( ColliderConstPtr collider );

private:
	Vector _pos;

	ModelPtr _model;
};

