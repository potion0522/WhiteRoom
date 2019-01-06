#pragma once
#include "Base.h"
#include <string>

PTR( Controller );
PTR( Scene );

class Controller : public Base {
public:
	enum SCENE {
		SCENE_CONTINUE,
		SCENE_TITLE,
		SCENE_GAME,
	};

public:
	static ControllerPtr getTask( );
	static std::string getTag( ) { return "CONTROLLER"; }

public:
	Controller( );
	virtual ~Controller( );

public:
	void initialize( );
	void update( );

	void setNextScene( SCENE next );

private:
	void loadScene( );

private:
	SCENE _next_scene;
	ScenePtr _scene;
};

