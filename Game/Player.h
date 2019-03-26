#pragma once
#include "SphereCollider.h"
#include "ElevatorAnnounce.h"
#include "ElevatorBox.h"
#include "smart_ptr.h"

/************************************************

Player�N���X
��ɃJ�����̐�����s��

************************************************/

PTR( Player );
PTR( ElevatorBox );
PTR( ConsoleActiveObservable );

class Player : public SphereCollider {
public:
	enum UPDATE_TYPE {
		UPDATE_TYPE_EYEONLY,
		UPDATE_TYPE_ALL
	};

public:
	Player( ElevatorBoxPtr elevator_box, ConsoleActiveObservablePtr console_observable );
	virtual ~Player( );

public:
	void update( );
	void setUpdateType( UPDATE_TYPE type );
	void onColliderEnter( ColliderConstPtr collider );
	FLOOR getFloor( ) const;

private:
	void actOnEyeOnly( );
	void actOnPlayerAll( );
	void updateDir( );
	void updatePos( );
	void updateEye( );
	void updateEar( );
	void updateFloor( );
	void adjustPosHitWall( ColliderConstPtr collider );

private:
	const double _PLAYER_COLLIDER_RADIUS;
	const double _HEIGHT;

private:
	UPDATE_TYPE _update_type;
	bool _console_active;
	Vector _ground_pos; // �v�Z�p(����)
	Vector _head_pos;  // �J�����p
	Vector _past_pos;  // �O����W(����)
	Vector _dir;
	FLOOR _floor;
	FLOOR _elevator_floor;
	ElevatorBoxPtr _elevator_box;
};

