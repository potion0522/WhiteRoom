#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

#include "define.h"

PTR( Collider );

class Collider {
public:
	Collider( const Vector& pos, OBJECT_TAG tag = OBJECT_TAG_NONE );
	virtual ~Collider( );

public:
	const Vector& getPos( ) const;
	OBJECT_TAG getTag( ) const;

public:
	virtual void onColliderEnter( ColliderPtr collider );

private:
	const Vector& _pos;
	OBJECT_TAG _tag;
};

