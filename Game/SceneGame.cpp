#include "SceneGame.h"
#include "Elevator.h"
#include "Console.h"
#include "CollideManager.h"
#include "Player.h"
#include "QuestionManager.h"
#include "Floor.h"
#include "Floor1.h"
#include "Floor2.h"

#include "Drawer.h"


SceneGame::SceneGame( ) {
	_question_manager       = QuestionManagerPtr( new QuestionManager );
	_collide_manager        = CollideManagerPtr( new CollideManager );
	_elevator               = ElevatorPtr( new Elevator( Vector( FLOOR_WIDTH / 2 + ELEVATOR_WIDTH / 2 + ELEVATOR_TO_FLOOR_SPACE, 0, 0 ), _collide_manager ) );
	_floors[ FLOOR_GF ]     = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ),FLOOR_GF ) );
	_floors[ FLOOR_1  ]     = Floor1Ptr( new Floor1( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager, FLOOR_1 ) );
	_floors[ FLOOR_2  ]     = Floor2Ptr( new Floor2( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager,FLOOR_2  ) );
	_floors[ FLOOR_3  ]     = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ),FLOOR_3  ) );
	_floors[ FLOOR_4  ]     = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ),FLOOR_4  ) );
	_floors[ FLOOR_5  ]     = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ),FLOOR_5  ) );
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
	drawer->flip( );
}