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
	_floor_1 = FloorPtr( new Floor( 0 ) );
	_elevator = ElevatorPtr( new Elevator( Vector( FLOOR_WIDTH + ELEVATOR_WIDTH, 0, 0 ) ) );
	_console = ConsolePtr( new Console( _elevator ) );
	_player = PlayerPtr( new Player );

	_collide_manager->addDynamicCollider( _player );
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
	_console->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}