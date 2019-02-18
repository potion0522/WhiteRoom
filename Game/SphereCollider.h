#pragma once
#include "Collider.h"
#include "Mathematics.h"

class SphereCollider : public Collider {
public:
	SphereCollider( const Vector& pos, double radius, OBJECT_TAG tag = OBJECT_TAG_NONE );
	virtual ~SphereCollider( );

public:
	const double& getRadius( ) const;

private:
	double _radius;
};

