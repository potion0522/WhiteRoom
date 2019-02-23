#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include "define.h"

#include <array>
#include <vector>

PTR( Elevator );
PTR( Model );
PTR( ElevatorAnnounce );
PTR( ElevatorAnnounceObservable );
PTR( Wall );
PTR( Door );
PTR( CollideManager );

class Elevator {
private:
	enum ELEVATOR_STATE {
		ELEVATOR_STATE_IDLE,
		ELEVATOR_STATE_MOVING,
		ELEVATOR_STATE_OPENING,
		ELEVATOR_STATE_CLOSING,
	};

public:
	Elevator( const Vector& init_pos, CollideManagerPtr collide_manager );
	virtual ~Elevator( );

public:
	void initializeCall( );
	void update( );
	void draw( ) const;
	ElevatorAnnounceObservablePtr getAnnounceObservable( ) const;
	void setMoveOrder( FLOOR floor );

private:
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
	Vector _pos;
	double _door_open_length;
	FLOOR _past_floor;
	FLOOR _floor;
	unsigned int _starting_time;
	ELEVATOR_STATE _state;

	ModelPtr _elevator_room;
	ModelPtr _elevator_door_left;
	ModelPtr _elevator_door_right;
	ElevatorAnnouncePtr _announce;

	std::array< WallPtr, WALL_COLLIDER_NUM > _wall_colliders;
	DoorPtr _door_collider;
};

