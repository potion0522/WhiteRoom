#include "Controller.h"
#include "Manager.h"

#include "SceneTitle.h"

ControllerPtr Controller::getTask( ) {
	return std::dynamic_pointer_cast< Controller >( Manager::getInstance( )->getTask( getTag( ) ) );
}

Controller::Controller( ) :
_next_scene( SCENE_TITLE ) {
}

Controller::~Controller( ) {
}

void Controller::initialize( ) {
	loadScene( );
}

void Controller::update( ) {
	_scene->update( );
	_scene->draw( );
}

void Controller::loadScene( ) {
	switch ( _next_scene ) {
	case SCENE_TITLE:
		_scene = SceneTitlePtr( new SceneTitle );
		break;

	case SCENE_GAME:
		break;
	}
}

void Controller::setNextScene( SCENE next ) {
}