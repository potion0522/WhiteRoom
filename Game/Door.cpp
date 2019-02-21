#include "Door.h"

Door::Door( Vector pos, Vector norm, double width, double height, OBJECT_TAG tag ) :
SquareCollider( _pos, norm, width, height, tag ),
_pos( pos ) {
}

Door::~Door( ) {
}
