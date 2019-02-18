#pragma once
#include "Collider.h"

#include "smart_ptr.h"
#include "Mathematics.h"

PTR( SquareCollider );

class SquareCollider : public Collider {
public:
	SquareCollider( const Vector& pos, Vector norm, double width, double height, OBJECT_TAG tag = OBJECT_TAG_NONE );
	virtual ~SquareCollider( );

public:
	const Vector& getNorm( ) const;
	const double& getWidth( ) const;
	const double& getHeight( ) const;

private:
	Vector _norm;
	double _width;
	double _height;
};

