#include "SceneGame.h"
#include "Controller.h"
#include "Elevator.h"
#include "Console.h"
#include "CollideManager.h"
#include "Player.h"
#include "QuestionManager.h"
#include "FloorGF.h"
#include "Floor1.h"
#include "Floor2.h"
#include "Floor3.h"
#include "Floor4.h"
#include "Floor5.h"

#include "Manager.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Image.h"

const char* FADE_IMAGE_FILEPATH = "White.png";

SceneGame::SceneGame( ) :
_phase( PHASE_WAIT ),
_time( 0 ),
_phase_count( PHASE_INIT ) {
	{ // whiteout
		DrawerPtr drawer = Drawer::getTask( );
		_fade_img = drawer->getImage( FADE_IMAGE_FILEPATH );
		_time = getNowCount( );
	}

	{ // モデル類
		_question_manager       = QuestionManagerPtr( new QuestionManager );
		_collide_manager        = CollideManagerPtr( new CollideManager );

		_elevator  = ElevatorPtr( new Elevator( Vector( ELEVATOR_INIT_X, ELEVATOR_INIT_Y, ELEVATOR_INIT_Z ), _collide_manager ) );

		_floors[ FLOOR_GF ]     = FloorPtr( new FloorGF( _collide_manager, _elevator->getAnnounceObservable( ) ) );
		_floors[ FLOOR_1  ]     = FloorPtr( new Floor1 ( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
		_floors[ FLOOR_2  ]     = FloorPtr( new Floor2 ( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
		_floors[ FLOOR_3  ]     = FloorPtr( new Floor3 ( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
		_floors[ FLOOR_4  ]     = FloorPtr( new Floor4 ( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
		_floors[ FLOOR_5  ]     = FloorPtr( new Floor5 ( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
		_console                = ConsolePtr( new Console( _elevator->getElevatorButton( ), _question_manager ) );
		_player                 = PlayerPtr( new Player( _elevator->getElevatorBox( ), _console->getActiveObservable( ) ) );

		// 当たり判定
		_collide_manager->addDynamicCollider( _player );
		_collide_manager->addDynamicCollider( _elevator );
	}
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	// 全phase共通update
	_collide_manager->update( );
	_elevator->update( );
	_player->update( );
	FLOOR player_floor = _player->getFloor( );
	_floors[ player_floor ]->update( );

	// phase毎update
	switch ( _phase ) {
	case PHASE_WAIT:
		updateWait( );
		break;

	case PHASE_PLAY:
		updatePlay( );
		break;

	case PHASE_GAMECLEAR:
		updateGameClear( );
		break;

	case PHASE_GAMEOVER:
		updateGameOver( );
		break;

	case PHASE_FADE_IN:
		updateFadeIn( );
		break;

	case PHASE_FADE_OUT:
		updateFadeOut( );
		break;
	}

	_phase_count++;

}

void SceneGame::draw( ) const {
	// 全phase共通描画
	_elevator->draw( );
	FLOOR player_floor = _player->getFloor( );
	_floors[ player_floor ]->draw( );

	// phase毎描画
	DrawerPtr drawer = Drawer::getTask( );
	switch ( _phase ) {
		case PHASE_WAIT: {
			_fade_img->draw( );
			drawer->drawFormatStringCenter( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0x000000, 50, "マウスクリックでゲームが始まります" );
		} break;

		case PHASE_PLAY: {
			_console->draw( );
		} break;

		case PHASE_GAMECLEAR: {
		} break;

		case PHASE_GAMEOVER: {
		} break;

		case PHASE_FADE_IN: { 
			_fade_img->draw( );
		} break;

		case PHASE_FADE_OUT: {
			_fade_img->draw( );
		} break;
	}

	drawer->waitForSync( ); // 30fpsにする
	drawer->flip( );
}

void SceneGame::updateWait( ) {
	if ( _phase_count == PHASE_INIT ) {
		_player->setUpdateType( Player::UPDATE_TYPE_EYEONLY );
	}

	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isClickUpLeft( ) ) {
		setPhase( PHASE_FADE_IN );
	}
}

void SceneGame::updatePlay( ) {
	if ( _phase_count == PHASE_INIT ) {
		_player->setUpdateType( Player::UPDATE_TYPE_ALL );
	}
	_console->update( );

	// clear
	if ( _player->getFloor( ) == FLOOR_GF ) {
		setPhase( PHASE_GAMECLEAR );
	}
}

void SceneGame::updateGameClear( ) {
	setPhase( PHASE_FADE_OUT );
}

void SceneGame::updateGameOver( ) {
}

void SceneGame::updateFadeIn( ) {
	// init
	if ( _phase_count == PHASE_INIT ) {
		_time = getNowCount( );
	}

	// phase変更
	int now = getNowCount( );
	if ( now - _time > FADE_TIME ) {
		setPhase( PHASE_PLAY );
	} else {
		//　fade alpha計算
		double ratio = ( now - _time ) / ( double )FADE_TIME;
		int alpha = ( int )( 255 * ( 1 - ratio ) );
		_fade_img->setBlendMode( alpha );
	}
}

void SceneGame::updateFadeOut( ) {
	// init
	if ( _phase_count == PHASE_INIT ) {
		_time = getNowCount( );
	}

	// phase変更
	int now = getNowCount( );
	if ( now - _time > FADE_TIME ) {
		Controller::getTask( )->setNextScene( Controller::SCENE_TITLE );
	} else {
		//　fade alpha計算
		double ratio = ( now - _time ) / ( double )FADE_TIME;
		int alpha = ( int )( 255 * ratio );
		_fade_img->setBlendMode( alpha );
	}
}

void SceneGame::setPhase( PHASE phase ) {
	_phase = phase;
	_phase_count = 0;
}

int SceneGame::getNowCount( ) const {
	return Manager::getInstance( )->getNowCount( );
}