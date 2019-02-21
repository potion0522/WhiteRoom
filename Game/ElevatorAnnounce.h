#pragma once
class ElevatorAnnounce {
public:
	virtual void announceArrive( int floor ) = 0;
	virtual void announceMove( ) = 0;
};

