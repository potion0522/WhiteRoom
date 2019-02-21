#include "Wall.h"

Wall::Wall( Vector pos, Vector norm, double width, double height, OBJECT_TAG tag ) :
SquareCollider( _pos, norm, width, height, tag ),
_pos( pos ) {
}

Wall::~Wall( ) {
}
