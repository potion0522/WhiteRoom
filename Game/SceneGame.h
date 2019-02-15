#pragma once
#include "smart_ptr.h"

#include "Scene.h"

PTR( SceneGame );
PTR( Floor );
PTR( Elevator );
PTR( Console );
PTR( CollideManager );
PTR( TestObject );

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
	TestObjectPtr _test;
};

