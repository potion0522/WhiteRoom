#pragma once
#include "SphereCollider.h"
#include "smart_ptr.h"

PTR( TestObject );

class TestObject : public SphereCollider {
public:
	TestObject( );
	virtual ~TestObject( );

public:
	void update( );
	void draw( ) const;

	void onColliderEnter( OBJECT_TAG tag );

private:
	Vector _past_pos;
	Vector _pos;
};

