#include "Collider.h"

Collider::Collider( const Vector& pos, TYPE type, OBJECT_TAG tag ) :
_pos( pos ),
_tag( tag ),
_type( type ),
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

Collider::TYPE Collider::getType( ) const {
	return _type;
}

void Collider::setEnabled( bool enabled ) {
	_enabled = enabled;
}

bool Collider::isEnabled( ) const {
	return _enabled;
}

void Collider::onColliderEnter( ColliderConstPtr collider ) {
}