#include "SceneGame.h"
#include "define.h"
#include "Floor.h"
#include "Elevator.h"
#include "Console.h"
#include "CollideManager.h"

#include "Drawer.h"
#include "Camera.h"
#include "Keyboard.h"

// debug
#include "TestObject.h"
#include "TestSquare.h"

SceneGame::SceneGame( ) {
	_collide_manager = CollideManagerPtr( new CollideManager );
	_floor_1 = FloorPtr( new Floor( 0 ) );
	_elevator = ElevatorPtr( new Elevator( Vector( FLOOR_WIDTH + ELEVATOR_WIDTH, 0, 0 ) ) );
	_console = ConsolePtr( new Console( _elevator ) );

	{ // debug
		_test = TestObjectPtr( new TestObject );
		_test_s = TestSquarePtr( new TestSquare );
	}

	_collide_manager->addStaticCollider( _elevator );
	_collide_manager->addDynamicCollider( _test );
	_collide_manager->addStaticCollider( _test_s );

	CameraPtr camera = Camera::getTask( );
	camera->setCameraUp( Vector( 0, 1, 0 ) );
	camera->setCamera( Vector( 0, 1, 0 ), Vector( 0, 1, 1 ) );
}

SceneGame::~SceneGame( ) {
}

void SceneGame::update( ) {
	_elevator->update( );
	_console->update( );
	_test->update( );

	// collider
	_collide_manager->update( );

	// debug
	DEBUG( );
}

void SceneGame::draw( ) const {
	_elevator->draw( );
	_floor_1->draw( );
	_console->draw( );
	_test->draw( );
	_test_s->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->flip( );
}

void SceneGame::DEBUG( ) {
	{ // debug
		KeyboardPtr keyboard = Keyboard::getTask( );
		static Vector camera;
		static Vector camera_dir = Vector( 0, 0, 1 );

		if ( keyboard->getKeyState( "RIGHT" ) ) {
			camera_dir = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -0.05 ).multiply( camera_dir );
		}
		if ( keyboard->getKeyState( "LEFT" ) ) {
			camera_dir = Matrix::makeTransformRotation( Vector( 0, 1, 0 ),  0.05 ).multiply( camera_dir );
		}

		
		if ( keyboard->getKeyState( "W" ) ) {
			camera += camera_dir *  100;
		}
		if ( keyboard->getKeyState( "S" ) ) {
			camera += camera_dir * -100;
		}
		if ( keyboard->getKeyState( "A" ) ) {
			camera += camera_dir.cross( Vector( camera_dir.x, camera_dir.y + 100, camera_dir.z ) ).normalize( ) *  100;
		}
		if ( keyboard->getKeyState( "D" ) ) {
			camera += camera_dir.cross( Vector( camera_dir.x, camera_dir.y + 100, camera_dir.z ) ).normalize( ) * -100;
		}
		if ( keyboard->getKeyState( "UP" ) ) {
			camera += Vector( 0,  1, 0 ) * 100;
		}
		if ( keyboard->getKeyState( "DOWN" ) ) {
			camera += Vector( 0, -1, 0 ) * 100;
		}
		Camera::getTask( )->setCamera( camera * 0.001, ( camera + camera_dir ) * 0.001 );
	} // !debug
}