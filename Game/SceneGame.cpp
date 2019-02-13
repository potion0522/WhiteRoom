#include "SceneGame.h"
#include "define.h"
#include "Floor.h"
#include "Elevator.h"
#include "Console.h"

#include "Drawer.h"
#include "Camera.h"
#include "Keyboard.h"

SceneGame::SceneGame( ) {
	_floor_1 = FloorPtr( new Floor( 0 ) );
	_elevator = ElevatorPtr( new Elevator( Vector( FLOOR_WIDTH + ELEVATOR_WIDTH, 0, 0 ) ) );
	_console = ConsolePtr( new Console( _elevator ) );

	CameraPtr camera = Camera::getTask( );
	camera->setCameraUp( Vector( 0, 1, 0 ) );
	camera->setCamera( Vector( 0, 1, 0 ), Vector( 0, 1, 1 ) );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	_elevator->update( );
	_console->update( );

	// debug
	DEBUG( );
}

void SceneGame::draw( ) const {
	_floor_1->draw( );
	_elevator->draw( );
	_console->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawSphere( Vector( ), 10, 50, 0xff0000, false );
	drawer->flip( );
}

void SceneGame::DEBUG( ) {
	{ // debug
		KeyboardPtr keyboard = Keyboard::getTask( );
		static int idx = 0;
		static double y = 0;
		Vector target[ 8 ] = {
			Vector(  0, y, 1 ),
			Vector(  1, y, 1 ),
			Vector(  1, y, 0 ),
			Vector(  1, y, -1 ),
			Vector(  0, y, -1 ),
			Vector( -1, y, -1 ),
			Vector( -1, y, 0 ),
			Vector( -1, y, 1 ),
		};

		if ( keyboard->getKeyDown( "ENTER" ) ) {
			idx = ( idx + 1 ) % 8;
		}
		if ( keyboard->getKeyState( "UP" ) ) {
			y += 0.2;
		}
		if ( keyboard->getKeyState( "DOWN" ) ) {
			y -= 0.2;
		}
		CameraPtr camera = Camera::getTask( );
		camera->setCamera( Vector( 0, y, 0 ), target[ idx ] );
		DrawerPtr drawer = Drawer::getTask( );
		drawer->drawFormatString( 0, 20, 0xff0000, "%.2lf : %.2lf", target[ idx ].y, y );

	} // !debug
}