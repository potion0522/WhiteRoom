#include "Question2Sphere.h"

Question2Sphere::Question2Sphere( Vector pos, ImagePtr texture, std::function< void( OBJECT_TAG ) > callback, OBJECT_TAG tag  ) :
Sphere( pos, _SPHERE_RADIUS, tag ) {
}

Question2Sphere::~Question2Sphere( ) {
}

void Question2Sphere::onColliderEnter( ColliderConstPtr collider ) {

}