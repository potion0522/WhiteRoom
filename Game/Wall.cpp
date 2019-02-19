#include "Wall.h"

Wall::Wall( Vector pos, Vector norm, double width, double height ) :
SquareCollider( _pos, norm, width, height, OBJECT_TAG_WALL ),
_pos( pos ) {
}

Wall::~Wall( ) {
}
