#include "SquareCollider.h"

SquareCollider::SquareCollider( const Vector& pos, double width, double height ) :
_pos( pos ),
_width( width ),
_height( height ) {
	_tag = OBJECT_TAG_NONE;
}

SquareCollider::~SquareCollider( ) {
}

const Vector& SquareCollider::getPos( ) const {
	return _pos;
}

const double& SquareCollider::getWidth( ) const {
	return _width;
}

const double& SquareCollider::getHeight( ) const {
	return _height;
}

OBJECT_TAG SquareCollider::getTag( ) const {
	return _tag;
}

void SquareCollider::onColliderEnter( OBJECT_TAG tag ) {
}