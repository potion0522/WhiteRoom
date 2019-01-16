#include "Manager.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"

#include "Controller.h"

int main( ) {
	// Framework
	DrawerPtr drawer( new Drawer( "Resources/Image" ) );
	KeyboardPtr keyboard( new Keyboard );
	MousePtr mouse( new Mouse );
	CameraPtr camera( new Camera );
	// WhiteRoom
	ControllerPtr controller( new Controller );

	// AddTask
	Manager* manager = Manager::getInstance( );
	manager->add( Controller::getTag( ), controller );
	manager->add( Drawer    ::getTag( ), drawer     );
	manager->add( Keyboard  ::getTag( ), keyboard   );
	manager->add( Mouse     ::getTag( ), mouse      );
	manager->add( Camera    ::getTag( ), camera     );
	return 0;
}