#include "SoundManager.h"
#include "Sound.h"
#include "Speaker.h"

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
const char* SE_ELEVATOR_OPEN    = "ElevatorOpen.mp3";
const char* SE_GAMESTART        = "GameStart.mp3";
const char* SE_GAMECLEAR        = "GameClear.mp3";

const char* SE_FILE[ SoundManager::MAX_SE ] = {
	SE_CONSOLE_OPEN    ,
	SE_CONSOLE_CLOSE   ,
	SE_CONSOLE_CLICK   ,
	SE_QUESTION_CLEAR  ,
	SE_QUESTION_UNCLEAR,
	SE_WALK            ,
	SE_ELEVATOR_MOVE   ,
	SE_ELEVATOR_ARRIVE ,
	SE_CONSOLE_SLIDE   ,
	SE_ELEVATOR_OPEN   ,
	SE_GAMESTART       ,
	SE_GAMECLEAR       ,
};

SoundManager::SoundManager( ) {
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
	for ( int i = 0; i < MAX_SE; i++ ) {

		std::list< SpeakerPtr >::iterator ite = _speakers[ i ].begin( );
		for ( ite; ite != _speakers[ i ].end( ); ite ) {
			if ( !( *ite )->isPlaying( ) ) {
				ite = _speakers[ i ].erase( ite );
				continue;
			}
			ite++;
		}
	}
}

void SoundManager::play( SE se ) {
	std::string file = SE_FILE[ se ];
	SoundPtr sound = Sound::getTask( );
	SpeakerPtr speaker = sound->load( file.c_str( ) );
	speaker->play( );

	_speakers[ se ].push_back( speaker );
}