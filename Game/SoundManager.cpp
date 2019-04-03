#include "SoundManager.h"
#include "define.h"

#include "Sound.h"
#include "Speaker2D.h"
#include "Speaker3D.h"

SoundManager* SoundManager::_instance;

const char* SE_CONSOLE_OPEN     = "SE/ConsoleOpen.mp3";
const char* SE_CONSOLE_CLOSE    = "SE/ConsoleClose.mp3";
const char* SE_CONSOLE_CLICK    = "SE/ConsoleClick.mp3";
const char* SE_CONSOLE_SLIDE    = "SE/ConsoleSlide.mp3";
const char* SE_QUESTION_CLEAR   = "SE/QuestionClear.mp3";
const char* SE_QUESTION_UNCLEAR = "SE/QuestionUnClear.mp3";
const char* SE_WALK             = "SE/Walk.mp3";
const char* SE_ELEVATOR_MOVE    = "SE/ElevatorMove.mp3";
const char* SE_ELEVATOR_ARRIVE  = "SE/ElevatorArrive.mp3";
const char* SE_GAMESTART        = "SE/GameStart.mp3";
const char* SE_GAMECLEAR        = "SE/GameClear.mp3";
const char* SE_SPHERE_DOCKING   = "SE/SphereDocking.mp3";

const char* BGM_TITLE = "BGM/Title.mp3";
const char* BGM_GAME  = "BGM/Game.mp3";

const char* SE_FILE[ SoundManager::MAX_SE ] = {
	SE_CONSOLE_OPEN    ,
	SE_CONSOLE_CLOSE   ,
	SE_CONSOLE_CLICK   ,
	SE_CONSOLE_SLIDE   ,
	SE_QUESTION_CLEAR  ,
	SE_QUESTION_UNCLEAR,
	SE_WALK            ,
	SE_ELEVATOR_MOVE   ,
	SE_ELEVATOR_ARRIVE ,
	SE_GAMESTART       ,
	SE_GAMECLEAR       ,
	SE_SPHERE_DOCKING
};

const char* BGM_FILE[ SoundManager::MAX_BGM ] = {
	BGM_TITLE,
	BGM_GAME
};

SoundManager::SoundManager( ) {
	for ( bool& flag : _mute_se ) {
		flag = false;
	}
}

SoundManager::~SoundManager( ) {
}

void SoundManager::finalize( ) {
	if ( _instance ) {
		delete _instance;
	}
}

SoundManager* SoundManager::getInstance( ) {
	if ( !_instance ) {
		_instance = new SoundManager;
	}

	return _instance;
}

void SoundManager::update( ) {
	{ // 2D
		std::list< Speaker2DPtr >::iterator ite = _speakers2D.begin( );
		for ( ite; ite != _speakers2D.end( ); ite ) {
			if ( !( *ite )->isPlaying( ) ) {
				ite = _speakers2D.erase( ite );
				continue;
			}
			ite++;
		}
	}


	// 3D
	for ( int i = 0; i < MAX_SE; i++ ) {
		std::list< Speaker3DPtr >::iterator ite = _speakers3D[ i ].begin( );
		for ( ite; ite != _speakers3D[ i ].end( ); ite ) {
			if ( !( *ite )->isPlaying( ) ) {
				ite = _speakers3D[ i ].erase( ite );
				continue;
			}
			ite++;
		}
	}
}

void SoundManager::play( SE se, const Vector& pos, float range ) {
	if ( isMute( se ) ) {
		return;
	}

	std::string file = SE_FILE[ se ];
	SoundPtr sound = Sound::getTask( );
	Speaker3DPtr speaker = sound->loadSound3D( file.c_str( ) );
	speaker->setPosition( pos * MIRI_TO_METER_UNIT );
	speaker->setRange( ( float )( range * MIRI_TO_METER_UNIT ) );
	speaker->setVolume( getVolume( se ) );
	speaker->play( );

	_speakers3D[ se ].push_back( speaker );
}

void SoundManager::play( SE se ) {
	if ( isMute( se ) ) {
		return;
	}

	std::string file = SE_FILE[ se ];
	SoundPtr sound = Sound::getTask( );
	Speaker2DPtr speaker = sound->loadSound2D( file.c_str( ) );
	speaker->play( );
	speaker->setVolume( getVolume( se ) );

	_speakers2D.push_back( speaker );
}

void SoundManager::play( BGM bgm ) {
	std::string file = BGM_FILE[ bgm ];

	SoundPtr sound = Sound::getTask( );
	Speaker2DPtr speaker = sound->loadSound2D( file.c_str( ) );
	speaker->setVolume( getVolume( bgm ) );
	speaker->setLoop( true );

	_bgm = speaker;
	_bgm->play( );
}

void SoundManager::stopBGM( ) {
	if ( _bgm ) {
		_bgm->stop( );
	}
}

void SoundManager::mute( SE se ) {
	_mute_se[ se ] = true;
}

void SoundManager::clearMute( ) {
	for ( bool& flag : _mute_se ) {
		flag = false;
	}
}

void SoundManager::set3DSoundPosition( SE se, const Vector& pos ) {
	if ( _speakers3D[ se ].empty( ) ) {
		return;
	}

	// ÅŒã‚Ìhandle‚Ì‚Ý“K—p
	Speaker3DPtr speaker = _speakers3D[ se ].back( );
	if ( speaker ) {
		speaker->setPosition( pos * MIRI_TO_METER_UNIT );
	}
}

bool SoundManager::isMute( SE se ) const {
	return _mute_se[ se ];
}

float SoundManager::getVolume( SE se ) const {
	float volume = 1.0f;
	switch ( se ) {
	case SE_CONSOLE_OPEN :
		volume = 1.0f;
		break;

	case SE_CONSOLE_CLOSE :
		volume = 1.0f;
		break;
	 
	case SE_CONSOLE_CLICK :
		volume = 0.75f;
		break;
	 
	case SE_CONSOLE_SLIDE :
		volume = 1.0f;
		break;
	 
	case SE_QUESTION_CLEAR :
		volume = 0.5f;
		break;
	 
	case SE_QUESTION_UNCLEAR :
		volume = 0.5f;
		break;
	 
	case SE_WALK :
		volume = 0.8f;
		break;
	 
	case SE_ELEVATOR_MOVE :
		volume = 1.0f;
		break;
	 
	case SE_ELEVATOR_ARRIVE :
		volume = 0.65f;
		break;
	 
	case SE_GAMESTART :
		volume = 0.65f;
		break;
	 
	case SE_GAMECLEAR :
		volume = 0.8f;
		break;

	case SE_SPHERE_DOCKING:
		volume = 2.0f;
		break;
	}

	return volume;
}

float SoundManager::getVolume( BGM bgm ) const {
	float volume = 1.0f;
	switch ( bgm ) {
	case BGM_TITLE :
		volume = 0.8f;
		break;

	case BGM_GAME :
		volume = 0.3f;
		break;
	}

	return volume;
}