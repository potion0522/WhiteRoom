#pragma once
#include "define.h"

class CollideNotifier {
public:
	virtual void onColliderEnter( OBJECT_TAG tag ) = 0;
	virtual OBJECT_TAG getTag( ) const = 0;

protected:
	OBJECT_TAG _tag;
};

