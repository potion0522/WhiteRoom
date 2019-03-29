#pragma once
#include "Sphere.h"
#include "smart_ptr.h"
#include "define.h"

#include <functional>

PTR( QuestionSphere );
PTR( Image );

class Question2Sphere : public Sphere {
public:
	Question2Sphere( Vector pos, ImagePtr texture, unsigned char charcolor_idx, std::function< void( OBJECT_TAG ) > callback, OBJECT_TAG tag );
	virtual ~Question2Sphere( );

public:
	void onColliderEnter( ColliderConstPtr collider );

private:
	std::function< void( OBJECT_TAG ) > _callback;
};

