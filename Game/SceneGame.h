#pragma once
#include "smart_ptr.h"

#include "Scene.h"

PTR( SceneGame );
PTR( Floor );
PTR( Elevator );
PTR( Console );
PTR( CollideManager );

// debug
PTR( TestObject );
PTR( TestSquare );

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
	CollideManagerPtr _collide_manager;
	FloorPtr _floor_1;
	ElevatorPtr _elevator;
	ConsolePtr _console;

	// debug class
	TestObjectPtr _test;
	TestSquarePtr _test_s;
};

