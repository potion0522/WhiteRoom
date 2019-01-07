#include "SceneGame.h"
#include "Floor.h"
#include "define.h"

#include "Drawer.h"
#include "Camera.h"
#include "Keyboard.h"

SceneGame::SceneGame( ) {
	_floor_1 = FloorPtr( new Floor( 0 ) );

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
		static double y = 0;
		Vector target[ 8 ] = {
			Vector( 0, y, 1 ),
			Vector( 1, y, 1 ),
			Vector( 1, y, 0 ),
			Vector( 1, y, -1 ),
			Vector( 0, y, -1 ),
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

void SceneGame::draw( ) const {
	_floor_1->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawSphere( Vector( ), 10, 50, 0xff0000, false );
	drawer->flip( );
}