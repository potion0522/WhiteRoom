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
PTR( UIActiveObservableComponent );

class Player : public SphereCollider {
public:
	enum UPDATE_TYPE {
		UPDATE_TYPE_EYEONLY,
		UPDATE_TYPE_ALL,
		UPDATE_TYPE_GAMECLEAR
	};

public:
	Player( ElevatorBoxPtr, UIActiveObservableComponentPtr );
	virtual ~Player( );

public:
	void update( );
	void setUpdateType( UPDATE_TYPE type );
	void onColliderEnter( ColliderConstPtr collider );
	FLOOR getFloor( ) const;

private:
	void actOnEyeOnly( );
	void actOnAllControll( );
	void actOnGameClearControll( );
	void initEyeOnly( );
	void initAllControll( );
	void initGameClearControll( );

	void updateDir( );
	void updatePos( );
	void walk( );
	void updateEye( );
	void updateEar( );
	void updateFloor( );
	void adjustPosHitWall( ColliderConstPtr collider );

private:
	UPDATE_TYPE _update_type;
	bool _ui_active;
	Vector _ground_pos; // �v�Z�p(����)
	Vector _head_pos;  // �J�����p
	Vector _past_pos;  // �O����W(����)
	double _sound_distance;
	Vector _dir;
	FLOOR _floor;
	FLOOR _elevator_floor;
	ElevatorBoxPtr _elevator_box;
};

