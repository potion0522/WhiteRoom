#pragma once
#include "Sphere.h"
#include "smart_ptr.h"
#include "define.h"

#include <functional>

PTR( QuestionSphere );
PTR( Image );

class Question2Sphere : public Sphere {
public:
	Question2Sphere( Vector pos, ImagePtr texture, std::function< void( OBJECT_TAG ) > callback, OBJECT_TAG tag );
	virtual ~Question2Sphere( );

public:
	void onColliderEnter( ColliderConstPtr collider );

private:
	const double _SPHERE_RADIUS = 1000.0;
};

