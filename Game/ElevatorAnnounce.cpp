#include "ElevatorAnnounce.h"

ElevatorAnnounce::ElevatorAnnounce( ) {
}

ElevatorAnnounce::~ElevatorAnnounce( ) {
}

void ElevatorAnnounce::subscribeAnnounceArrive( std::function< void( FLOOR floor ) > func ) {
	_announce_arrive.push_back( func );
}

void ElevatorAnnounce::subscribeAnnounceMove( std::function< void( ) > func ) {
	_announce_move.push_back( func );
}

void ElevatorAnnounce::announceArrive( FLOOR floor ) {
	for ( int i = 0; i < _announce_arrive.size( ); i++ ) {
		_announce_arrive[ i ]( floor );
	}
}

void ElevatorAnnounce::announceMove( ) {
	for ( int i = 0; i < _announce_move.size( ); i++ ) {
		_announce_move[ i ]( );
	}
}