#pragma once
#include "SquareCollider.h"
#include "smart_ptr.h"

/*
	Floorの壁の当たり判定用のクラス
*/

PTR( Wall );

class Wall : public SquareCollider {
public:
	Wall( Vector pos, Vector norm, double width, double height );
	virtual ~Wall( );

private:
	Vector _pos;
};

