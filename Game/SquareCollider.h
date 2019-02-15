#pragma once
#include "CollideNotifier.h"

#include "smart_ptr.h"
#include "Mathematics.h"

PTR( SquareCollider );

class SquareCollider : public CollideNotifier {
public:
	SquareCollider( const Vector& pos, double width, double height );
	virtual ~SquareCollider( );

public:
	const Vector& getPos( ) const;
	const double& getWidth( ) const;
	const double& getHeight( ) const;
	OBJECT_TAG getTag( ) const;
	void onColliderEnter( OBJECT_TAG tag );

private:
	const Vector& _pos;
	double _width;
	double _height;
};

