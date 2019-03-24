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
PTR( Image );

class SceneGame : public Scene {
private:
	enum PHASE {
		PHASE_WAIT,
		PHASE_PLAY,
		PHASE_GAMECLEAR,
		PHASE_GAMEOVER,
		PHASE_FADE_IN,
		PHASE_FADE_OUT,
	};

public:
	SceneGame( );
	virtual ~SceneGame( );

public:
	void update( );
	void draw( ) const;

private:
	void updateWait( );
	void updatePlay( );
	void updateGameClear( );
	void updateGameOver( );
	void updateFadeIn( );
	void updateFadeOut( );
	void setPhase( PHASE phase );
	int getNowCount( ) const;

private:
	const int PHASE_INIT = 1;
	const int FADE_TIME = 1500;

private:
	PHASE _phase;
	int _time;
	int _phase_count;

	ImagePtr _fade_img;
	CollideManagerPtr _collide_manager;
	std::array< FloorPtr, MAX_FLOOR > _floors;
	ElevatorPtr _elevator;
	ConsolePtr _console;
	PlayerPtr _player;
	QuestionManagerPtr _question_manager;
};

