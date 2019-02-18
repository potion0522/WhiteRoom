#pragma once
#include "smart_ptr.h"

#include "define.h"

#include <vector>
#include <list>

PTR( SphereCollider );
PTR( SquareCollider );

class CollideManager {
public:
	CollideManager( );
	virtual ~CollideManager( );

public:
	void update( );

public:
	void addDynamicCollider( SphereColliderWeakPtr collider );
	void addStaticCollider( SphereColliderPtr collider );
	void addStaticCollider( SquareColliderPtr collider );

private:
	void detectDynamicToDynamicObject( );
	void detectDynamicToStaticObject( );
	bool isCollideSphereAndSphere( SphereColliderPtr collider1, SphereColliderPtr collider2 );
	bool isCollideSphereAndSquare( SphereColliderPtr collider1, SquareColliderPtr collider2 );

private:
	std::list< SphereColliderWeakPtr > _dynamic_sphere_obj;

	std::vector< SphereColliderPtr > _static_sphere_obj;
	std::vector< SquareColliderPtr > _static_square_obj;
};

