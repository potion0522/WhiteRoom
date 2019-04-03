#include "SphereCollider.h"

SphereCollider::SphereCollider( const Vector& pos, double radius, OBJECT_TAG tag ) :
Collider( pos, Collider::TYPE_SPHERE, tag ),
_radius( radius ) {
}

SphereCollider::~SphereCollider( ) {
}

const double& SphereCollider::getRadius( ) const {
	return _radius;
}