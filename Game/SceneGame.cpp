#include "SceneGame.h"
#include "define.h"
#include "Floor.h"
#include "Elevator.h"
#include "Console.h"
#include "CollideManager.h"
#include "Player.h"

#include "Drawer.h"


SceneGame::SceneGame( ) {
	_collide_manager = CollideManagerPtr( new CollideManager );

	_elevator = ElevatorPtr( new Elevator( Vector( FLOOR_WIDTH / 2 + ELEVATOR_WIDTH / 2, 0, 0 ), _collide_manager ) );
	_floor_1 = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ), FLOOR_GF ) );
	_floor_2 = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ), FLOOR_1 ) );
	_console = ConsolePtr( new Console( _elevator ) );
	_player = PlayerPtr( new Player );

	// 当たり判定
	_collide_manager->addDynamicCollider( _player );

	// エレベーターイベント
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	_player->update( );
	_elevator->update( );
	_console->update( );

	// collider
	_collide_manager->update( );
}

void SceneGame::draw( ) const {
	_elevator->draw( );
	_floor_1->draw( );
	_floor_2->draw( );
	_console->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}