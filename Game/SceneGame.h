#pragma once
#include "smart_ptr.h"

#include "Scene.h"

PTR( SceneGame );
PTR( Floor );
PTR( Elevator );

class SceneGame : public Scene {
public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	FloorPtr _floor_1;
	ElevatorPtr _elevator;
};

