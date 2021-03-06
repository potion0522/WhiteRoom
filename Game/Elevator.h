#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include "define.h"
#include "SphereCollider.h"

#include <array>
#include <vector>

/*************************************************************

エレベーター全体を管理しているクラス
移動依頼、搭乗依頼はそれぞれ別の場所が受け取る

*************************************************************/

PTR( Elevator );
PTR( Model );
PTR( ElevatorAnnounce );
PTR( ElevatorAnnounceObservable );
PTR( Wall );
PTR( Door );
PTR( CollideManager );
PTR( ElevatorButton );
PTR( ElevatorBox );

class Elevator : public SphereCollider {
private:
	enum ELEVATOR_STATE {
		ELEVATOR_STATE_IDLE,
		ELEVATOR_STATE_MOVING,
		ELEVATOR_STATE_OPENING,
		ELEVATOR_STATE_CLOSING,
	};

public:
	Elevator( const Vector& init_pos, CollideManagerPtr collide_manager, FLOOR init_floor = ELEVATOR_INIT_FLOOR );
	virtual ~Elevator( );

public:
	void update( );
	void draw( ) const;
	ElevatorAnnounceObservablePtr getAnnounceObservable( ) const;
	ElevatorButtonPtr getElevatorButton( ) const;
	ElevatorBoxPtr getElevatorBox( ) const;

private:
	void requestMoveElevatorButtonToElevator( FLOOR order );
	void requextRideElevatorBoxToElevator( Vector* obj_pos );
	bool isItPossibleToOrderElevator( ) const;
	int getNowCount( ) const;
	void actOnIdle( );
	void actOnMoving( );
	void actOnOpening( );
	void actOnClosing( );
	void generateElevator( );
	void generateElevatorCollider( );

private:
	static const int WALL_COLLIDER_NUM = 3;

private:
	Vector _pos; // 床
	Vector _sphere_collider_pos; // 部屋の中心
	double _door_open_length;
	FLOOR _past_floor;
	FLOOR _floor;
	unsigned int _starting_time;
	ELEVATOR_STATE _state;
	std::vector< Vector* > _ride_obj;

	ModelPtr _elevator_room;
	ModelPtr _elevator_door_left;
	ModelPtr _elevator_door_right;
	ModelPtr _elevator_wall;
	ElevatorAnnouncePtr _announce;
	ElevatorButtonPtr _elevator_button;
	ElevatorBoxPtr _elevator_box;

	std::array< WallPtr, WALL_COLLIDER_NUM > _wall_colliders;
	DoorPtr _door_collider;
};

