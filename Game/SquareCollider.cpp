#include "SquareCollider.h"

SquareCollider::SquareCollider( const Vector& pos, Vector norm, double width, double height, OBJECT_TAG tag ) :
Collider( pos, tag ),
_norm( norm ),
_width( width ),
_height( height ) {
}

SquareCollider::~SquareCollider( ) {
}

const Vector& SquareCollider::getNorm( ) const {
	return _norm;
}

const double& SquareCollider::getWidth( ) const {
	return _width;
}

const double& SquareCollider::getHeight( ) const {
	return _height;
}