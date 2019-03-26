#pragma once
#include "smart_ptr.h"
#include <array>
#include <list>

PTR( Speaker );

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
	void play( SE se );
	void mute( SE se );
	void clearMute( );

private:
	bool isMute( SE se ) const;

private:
	static SoundManager* _instance;

private:
	std::array< std::list< SpeakerPtr >, MAX_SE > _speakers;
	std::array< bool, MAX_SE > _mute_se;
};

