#include "SoundManager.h"
#include "Sound.h"
#include "Speaker2D.h"
#include "Speaker3D.h"

SoundManager* SoundManager::_instance;

const char* SE_CONSOLE_OPEN     = "ConsoleOpen.mp3";
const char* SE_CONSOLE_CLOSE    = "ConsoleClose.mp3";
const char* SE_CONSOLE_CLICK    = "ConsoleClick.mp3";
const char* SE_CONSOLE_SLIDE    = "ConsoleSlide.mp3";
const char* SE_QUESTION_CLEAR   = "QuestionClear.mp3";
const char* SE_QUESTION_UNCLEAR = "QuestionUnClear.mp3";
const char* SE_WALK             = "Walk.mp3";
const char* SE_ELEVATOR_MOVE    = "ElevatorMove.mp3";
const char* SE_ELEVATOR_ARRIVE  = "ElevatorArrive.mp3";
const char* SE_GAMESTART        = "GameStart.mp3";
const char* SE_GAMECLEAR        = "GameClear.mp3";

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
	speaker->setPosition( pos );
	speaker->setRange( range );
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

	_speakers2D.push_back( speaker );
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
		speaker->setPosition( pos );
	}
}

bool SoundManager::isMute( SE se ) const {
	return _mute_se[ se ];
}