#include "SceneGame.h"
#include "Floor.h"
#include "Elevator.h"
#include "Console.h"
#include "CollideManager.h"
#include "Player.h"
#include "QuestionManager.h"

#include "Drawer.h"


SceneGame::SceneGame( ) {
	_question_manager = QuestionManagerPtr( new QuestionManager );
	_collide_manager = CollideManagerPtr( new CollideManager );

	_elevator = ElevatorPtr( new Elevator( Vector( FLOOR_WIDTH / 2 + ELEVATOR_WIDTH / 2 + ELEVATOR_TO_FLOOR_SPACE, 0, 0 ), _collide_manager ) );
	for ( int i = 0; i < MAX_FLOOR; i++ ) {
		_floors[ i ] = FloorPtr( new Floor( _collide_manager, _elevator->getAnnounceObservable( ), _question_manager, ( FLOOR )i ) );
	}
	_console = ConsolePtr( new Console( _elevator->getElevatorButton( ) ) );
	_player = PlayerPtr( new Player( _elevator->getElevatorBox( ), _console->getActiveObservable( ) ) );

	// “–‚½‚è”»’è
	_collide_manager->addDynamicCollider( _player );
	_collide_manager->addDynamicCollider( _elevator );
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

	for ( int i = 0; i < MAX_FLOOR; i++ ) {
		_floors[ i ]->draw( );
	}

	_console->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}