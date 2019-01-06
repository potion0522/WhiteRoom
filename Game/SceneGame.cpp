#include "SceneGame.h"
#include "Room.h"

#include "Drawer.h"
#include "Camera.h"
#include "Keyboard.h"

SceneGame::SceneGame( ) {
	_room_1 = RoomPtr( new Room( 0 ) );

	CameraPtr camera = Camera::getTask( );
	camera->setCameraUp( Vector( 0, 1, 0 ) );
	camera->setCamera( Vector( 0, 1, 0 ), Vector( 0, 1, 1 ) );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	{ // debug
		KeyboardPtr keyboard = Keyboard::getTask( );
		static int idx = 0;
		static Vector target[ 8 ] = {
			Vector( 0, 1, 1 ),
			Vector( 1, 1, 1 ),
			Vector( 1, 1, 0 ),
			Vector( 1, 1, -1 ),
			Vector( 0, 1, -1 ),
			Vector( -1, 1, -1 ),
			Vector( -1, 1, 0 ),
			Vector( -1, 1, 1 ),
		};

		if ( keyboard->getKeyDown( "ENTER" ) ) {
			idx = ( idx + 1 ) % 8;
		}
		CameraPtr camera = Camera::getTask( );
		camera->setCamera( Vector( 0, 1, 0 ), target[ idx ] );
	} // !debug
}

void SceneGame::draw( ) const {
	_room_1->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawSphere( Vector( ), 10, 50, 0xff0000, false );
	drawer->flip( );
}