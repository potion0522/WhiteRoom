#pragma once
#include "SphereCollider.h"
#include "ElevatorAnnounce.h"
#include "smart_ptr.h"

PTR( Player );

class Player : public SphereCollider, public ElevatorAnnounce {
public:
	Player( );
	virtual ~Player( );

public:
	void update( );
	void onColliderEnter( ColliderConstPtr collider );
	void announceArrive( int floor );
	void announceMove( );

private:
	void updateDir( );
	void updatePos( );
	void updateEye( );
	void adjustPosHitWall( ColliderConstPtr collider );

private:
	const double _PLAYER_COLLIDER_RADIUS;
	const double _HEIGHT;

private:
	bool _elevator_moving;
	Vector _ground_pos; // 計算用(足元)
	Vector _head_pos;  // カメラ用
	Vector _past_pos;  // 前回座標(足元)
	Vector _dir;
	FLOOR _floor;
	FLOOR _elevator_floor;
};

