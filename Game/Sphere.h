#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include "SphereCollider.h"

/**************************************************

‹…‘Ì‚»‚Ì‚à‚Ì‚ÌƒNƒ‰ƒX

**************************************************/


PTR( Model );

class Sphere : public SphereCollider {
public:
	Sphere( Vector pos, double radius, OBJECT_TAG tag = OBJECT_TAG_SPHERE );
	virtual ~Sphere( );

public:
	void draw( ) const;
	virtual void onColliderEnter( ColliderConstPtr collider );

private:
	void generate( );

private:
	static const int _DIV_NUM = 30;

protected:
	ModelPtr _model;
	Vector _pos;
	double _radius;
};

