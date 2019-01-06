#include "Manager.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Mouse.h"

#include "Controller.h"

int main( ) {
	// Framework
	DrawerPtr drawer( new Drawer( "Resources/Image" ) );
	KeyboardPtr keyboard( new Keyboard );
	MousePtr mouse( new Mouse );

	// WhiteRoom
	ControllerPtr controller( new Controller );

	// AddTask
	Manager* manager = Manager::getInstance( );
	manager->add( Controller::getTag( ), controller );
	manager->add( Drawer    ::getTag( ), drawer     );
	manager->add( Keyboard  ::getTag( ), keyboard   );
	manager->add( Mouse     ::getTag( ), mouse      );
	return 0;
}