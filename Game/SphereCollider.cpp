#include "SphereCollider.h"

SphereCollider::SphereCollider( const Vector& pos, double radius ) :
_pos( pos ),
_radius( radius ) {
	_tag = OBJECT_TAG_NONE;
}

SphereCollider::~SphereCollider( ) {
}

const Vector& SphereCollider::getPos( ) const {
	return _pos;
}

const double& SphereCollider::getRadius( ) const {
	return _radius;
}

OBJECT_TAG SphereCollider::getTag( ) const {
	return _tag;
}

void SphereCollider::onColliderEnter( OBJECT_TAG tag ) {
}