#include "Question2Sphere.h"
#include "Model.h"

Question2Sphere::Question2Sphere( Vector pos, ImagePtr texture, unsigned char color_idx, std::function< void( OBJECT_TAG ) > callback, OBJECT_TAG tag  ) :
Sphere( pos, SPHERE_OBJECT_RADIUS, color_idx, tag ),
_callback( callback ) {
	_model->setTexture( texture );
}

Question2Sphere::~Question2Sphere( ) {
}

void Question2Sphere::onColliderEnter( ColliderConstPtr collider ) {
	OBJECT_TAG tag = collider->getTag( );

	if ( tag == OBJECT_TAG_Q2SPHERE_1 ||
		 tag == OBJECT_TAG_Q2SPHERE_2 ||
		 tag == OBJECT_TAG_Q2SPHERE_3 ||
		 tag == OBJECT_TAG_Q2SPHERE_4 ||
		 tag == OBJECT_TAG_Q2SPHERE_5 ) {
		_callback( tag );
	}

	Sphere::onColliderEnter( collider );
}