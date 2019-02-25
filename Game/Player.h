#pragma once
#include "SphereCollider.h"
#include "ElevatorAnnounce.h"
#include "ElevatorBox.h"
#include "smart_ptr.h"

PTR( Player );
PTR( ElevatorBox );
PTR( ConsoleActiveObservable );

class Player : public SphereCollider {
public:
	Player( ElevatorBoxPtr elevator_box, ConsoleActiveObservablePtr console_observable );
	virtual ~Player( );

public:
	void update( );
	void onColliderEnter( ColliderConstPtr collider );

private:
	void updateDir( );
	void updatePos( );
	void updateEye( );
	void adjustPosHitWall( ColliderConstPtr collider );

private:
	const double _PLAYER_COLLIDER_RADIUS;
	const double _HEIGHT;

private:
	bool _console_active;
	Vector _ground_pos; // 計算用(足元)
	Vector _head_pos;  // カメラ用
	Vector _past_pos;  // 前回座標(足元)
	Vector _dir;
	FLOOR _floor;
	FLOOR _elevator_floor;
	ElevatorBoxPtr _elevator_box;
};

