#pragma once
#include "smart_ptr.h"

#include "Scene.h"
#include "define.h"
#include <array>

PTR( SceneGame );
PTR( Floor );
PTR( Elevator );
PTR( Console );
PTR( CollideManager );
PTR( Player );
PTR( QuestionManager );

class SceneGame : public Scene {
public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	CollideManagerPtr _collide_manager;
	std::array< FloorPtr, MAX_FLOOR > _floors;
	ElevatorPtr _elevator;
	ConsolePtr _console;
	PlayerPtr _player;
	QuestionManagerPtr _question_manager;
};

