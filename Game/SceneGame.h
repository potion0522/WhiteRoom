#pragma once
#include "smart_ptr.h"

#include "Scene.h"

PTR( SceneGame );
PTR( Room );

class SceneGame : public Scene {
public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	RoomPtr _room_1;
};

