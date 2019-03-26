#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include <array>
#include <list>

PTR( Speaker2D );
PTR( Speaker3D );

class SoundManager {
public:
	enum SE {
		SE_CONSOLE_OPEN,
		SE_CONSOLE_CLOSE,
		SE_CONSOLE_CLICK,
		SE_CONSOLE_SLIDE,
		SE_QUESTION_CLEAR,
		SE_QUESTION_UNCLEAR,
		SE_WALK,
		SE_ELEVATOR_MOVE,
		SE_ELEVATOR_ARRIVE,
		SE_GAMESTART,
		SE_GAMECLEAR,
		MAX_SE
	};

private:
	SoundManager( );
	virtual ~SoundManager( );

public:
	static SoundManager* getInstance( );

public:
	void finalize( );
	void update( );
	void mute( SE se );
	void clearMute( );
	void set3DSoundPosition( SE se, const Vector& pos );
	void play( SE se, const Vector& pos, float range ); // 3D
	void play( SE se ); // 2D

private:
	bool isMute( SE se ) const;

private:
	static SoundManager* _instance;

private:
	std::list< Speaker2DPtr > _speakers2D;
	std::array< std::list< Speaker3DPtr >, MAX_SE > _speakers3D;

	std::array< bool, MAX_SE > _mute_se;
};

