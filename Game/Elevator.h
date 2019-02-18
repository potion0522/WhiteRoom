#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

#include "SphereCollider.h"

PTR( Elevator );
PTR( Model );

class Elevator : public SphereCollider {
private:
	enum ELEVATOR_STATE {
		ELEVATOR_STATE_IDLE,
		ELEVATOR_STATE_MOVING,
		ELEVATOR_STATE_OPENING,
		ELEVATOR_STATE_CLOSING,
	};

public:
	Elevator( const Vector& init_pos );
	virtual ~Elevator( );

public:
	void update( );
	void setMoveOrder( int order_floor );
	void draw( ) const;

private:
	bool isItPossibleToOrderElevator( ) const;
	int getNowCount( ) const;
	void actOnIdle( );
	void actOnMoving( );
	void actOnOpening( );
	void actOnClosing( );
	void generateElevator( );

private:
	Vector _elevator_pos;
	double _door_open_length;
	unsigned char _past_floor;
	unsigned char _floor;
	unsigned int _starting_time;
	ELEVATOR_STATE _state;

	ModelPtr _elevator_room;
	ModelPtr _elevator_door_left;
	ModelPtr _elevator_door_right;
};

