#pragma once
#include "SquareCollider.h"
#include "smart_ptr.h"

/*
	Floor�̕ǂ̓����蔻��p�̃N���X
*/

PTR( Wall );

class Wall : public SquareCollider {
public:
	Wall( Vector pos, Vector norm, double width, double height, OBJECT_TAG tag = OBJECT_TAG_WALL );
	virtual ~Wall( );

private:
	Vector _pos;
};

