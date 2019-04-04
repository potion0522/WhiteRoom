#pragma once
#include "SphereCollider.h"
#include "ElevatorAnnounce.h"
#include "ElevatorBox.h"
#include "smart_ptr.h"

/************************************************

Playerクラス
主にカメラの制御を行う

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
	Vector _ground_pos; // 計算用(足元)
	Vector _head_pos;  // カメラ用
	Vector _past_pos;  // 前回座標(足元)
	double _sound_distance;
	Vector _dir;
	FLOOR _floor;
	FLOOR _elevator_floor;
	ElevatorBoxPtr _elevator_box;
};

