#pragma once
#include "SphereCollider.h"
#include "smart_ptr.h"

PTR( Player );

class Player : public SphereCollider {
public:
	Player( );
	virtual ~Player( );

public:
	void update( );
	void onColliderEnter( ColliderConstPtr collider );

private:
	void updateDir( );
	void updatePos( );
	void updateEye( );

private:
	const double _PLAYER_COLLIDER_RADIUS;
	const double _HEIGHT;

private:
	Vector _ground_pos; // �v�Z�p(����)
	Vector _head_pos;  // �J�����p
	Vector _past_pos;  // �O����W(����)
	Vector _dir;
	unsigned char _floor;
};
