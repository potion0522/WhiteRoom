#pragma once
#include "Sphere.h"
#include "smart_ptr.h"

PTR( DummySphere );
PTR( Sphere );
PTR( CollideManager );

class DummySphere {
public:
	DummySphere( CollideManagerPtr collide_manager, FLOOR floor, int color_idx );
	virtual ~DummySphere( );

public:
	void update( );
	void draw( ) const;

private:
	SpherePtr _sphere;
};

