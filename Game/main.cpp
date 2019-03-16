#include "Manager.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "Random.h"

#include "Controller.h"
#include "define.h"

int main( ) {
	// Setting
	Manager* manager = Manager::getInstance( );
	manager->setScreenSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	manager->setWindowSize( 1280, 720 );
	manager->setUseZBaffur( true );
	manager->setWriteZBaffur( true );

	// Framework
	DrawerPtr drawer( new Drawer( "Resources/Image" ) );
	KeyboardPtr keyboard( new Keyboard );
	MousePtr mouse( new Mouse );
	CameraPtr camera( new Camera );
	RandomPtr rand( new Random );

	// WhiteRoom
	ControllerPtr controller( new Controller );

	// AddTask
	manager->add( Controller::getTag( ), controller );
	manager->add( Drawer    ::getTag( ), drawer     );
	manager->add( Keyboard  ::getTag( ), keyboard   );
	manager->add( Mouse     ::getTag( ), mouse      );
	manager->add( Camera    ::getTag( ), camera     );
	manager->add( Random    ::getTag( ), rand       );
	return 0;
}