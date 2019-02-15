#pragma once
#include "CollideNotifier.h"
#include "Mathematics.h"

class SphereCollider : public CollideNotifier {
public:
	SphereCollider( const Vector& pos, double radius );
	virtual ~SphereCollider( );

public:
	const Vector& getPos( ) const;
	const double& getRadius( ) const;
	OBJECT_TAG getTag( ) const;
	void onColliderEnter( OBJECT_TAG tag );

private:
	const Vector& _pos;
	double _radius;
};

