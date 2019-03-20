#include "SceneGame.h"
#include "Elevator.h"
#include "Console.h"
#include "CollideManager.h"
#include "Player.h"
#include "QuestionManager.h"
#include "Floor.h"
#include "Floor1.h"
#include "Floor2.h"
#include "Floor3.h"
#include "Floor4.h"
#include "Floor5.h"

#include "Drawer.h"


SceneGame::SceneGame( ) {
	_question_manager       = QuestionManagerPtr( new QuestionManager );
	_collide_manager        = CollideManagerPtr( new CollideManager );

	_elevator  = ElevatorPtr( new Elevator( Vector( ELEVATOR_INIT_X, ELEVATOR_INIT_Y, ELEVATOR_INIT_Z ), _collide_manager ) );

	_floors[ FLOOR_GF ]     = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ), FLOOR_GF ) );
	_floors[ FLOOR_1  ]     = Floor1Ptr( new Floor1( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
	_floors[ FLOOR_2  ]     = Floor2Ptr( new Floor2( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
	_floors[ FLOOR_3  ]     = Floor3Ptr( new Floor3( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
	_floors[ FLOOR_4  ]     = Floor4Ptr( new Floor4( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
	_floors[ FLOOR_5  ]     = Floor5Ptr( new Floor5( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager ) );
	_console                = ConsolePtr( new Console( _elevator->getElevatorButton( ), _question_manager ) );
	_player                 = PlayerPtr( new Player( _elevator->getElevatorBox( ), _console->getActiveObservable( ) ) );

	// “–‚½‚è”»’è
	_collide_manager->addDynamicCollider( _player );
	_collide_manager->addDynamicCollider( _elevator );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	// collider
	_collide_manager->update( );

	_player->update( );
	_elevator->update( );
	_console->update( );

	FLOOR player_floor = _player->getFloor( );
	_floors[ player_floor ]->update( );
}

void SceneGame::draw( ) const {
	_elevator->draw( );

	FLOOR player_floor = _player->getFloor( );
	_floors[ player_floor ]->draw( );

	_console->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( ); // 30fps‚É‚·‚é
	drawer->drawFPS( );
	drawer->flip( );
}