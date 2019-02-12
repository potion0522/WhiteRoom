#pragma once
#include "smart_ptr.h"

#include "Scene.h"

PTR( SceneGame );
PTR( Floor );
PTR( Elevator );
PTR( Console );

class SceneGame : public Scene {
public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	void DEBUG( );

private:
	FloorPtr _floor_1;
	ElevatorPtr _elevator;
	ConsolePtr _console;
};

