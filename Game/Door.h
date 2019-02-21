#pragma once
#include "SquareCollider.h"
#include "smart_ptr.h"

/*
	Floor�̕ǂ̓����蔻��p�̃N���X
*/

PTR( Door );

class Door : public SquareCollider {
public:
	Door( Vector pos, Vector norm, double width, double height, OBJECT_TAG tag = OBJECT_TAG_ELEVATOR_DOOR );
	virtual ~Door( );

private:
	Vector _pos;
};
