#include "Collider.h"

Collider::Collider( const Vector& pos, OBJECT_TAG tag ) :
_pos( pos ),
_tag( tag ) {
}

Collider::~Collider( ) {
}

const Vector& Collider::getPos( ) const {
	return _pos;
}

OBJECT_TAG Collider::getTag( ) const {
	return _tag;
}

void Collider::onColliderEnter( ColliderPtr collider ) {
}