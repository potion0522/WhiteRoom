#include "Manager.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "Random.h"
#include "Sound.h"

#include "Controller.h"
#include "define.h"

/************************************************

初期設定、クラスの登録を行う
ゲームのシーン管理はControllerで行い、
メインループはFramework->Managerで行われる

************************************************/

int main( ) {
	// Setting
	Manager* manager = Manager::getInstance( );
	manager->setScreenSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	#ifdef DEBUG
		manager->setWindowSize( 1280, 720 );
	#endif
	manager->setUseZBaffur( true );
	manager->setWriteZBaffur( true );
	manager->setUseLighting( true );
	manager->setUseLightTypeDir( true );
	manager->setLightAmbient( 0.3f, 0.3f, 0.3f );

	// Framework
	DrawerPtr drawer( new Drawer( "Resources/Image" ) );
	KeyboardPtr keyboard( new Keyboard );
	MousePtr mouse( new Mouse );
	CameraPtr camera( new Camera );
	RandomPtr rand( new Random );
	SoundPtr sound( new Sound( "Resources/Sound" ) );

	// WhiteRoom
	ControllerPtr controller( new Controller );

	// AddTask
	manager->add( Controller::getTag( ), controller );
	manager->add( Drawer    ::getTag( ), drawer     );
	manager->add( Keyboard  ::getTag( ), keyboard   );
	manager->add( Mouse     ::getTag( ), mouse      );
	manager->add( Camera    ::getTag( ), camera     );
	manager->add( Random    ::getTag( ), rand       );
	manager->add( Sound     ::getTag( ), sound      );
	return 0;
}