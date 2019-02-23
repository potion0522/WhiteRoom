#include "Collider.h"

Collider::Collider( const Vector& pos, OBJECT_TAG tag ) :
_pos( pos ),
_tag( tag ),
_enabled( true ) {
}

Collider::~Collider( ) {
}

const Vector& Collider::getPos( ) const {
	return _pos;
}

OBJECT_TAG Collider::getTag( ) const {
	return _tag;
}

void Collider::setEnabled( bool enabled ) {
	_enabled = enabled;
}

bool Collider::isEnabled( ) const {
	return _enabled;
}

void Collider::onColliderEnter( ColliderConstPtr collider ) {
}