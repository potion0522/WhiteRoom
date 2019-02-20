#include "TestObject.h"
#include "Keyboard.h"
#include "Drawer.h"

TestObject::TestObject( ) :
SphereCollider( _pos, 100 ) {
}

TestObject::~TestObject( ) {
}

void TestObject::update( ) {
	_past_pos = _pos;

	KeyboardPtr keyboard = Keyboard::getTask( );
	if ( keyboard->getKeyState( "T" ) ) {
		_pos += Vector( 0, 0, 10 );
	}
	if ( keyboard->getKeyState( "F" ) ) {
		_pos += Vector( -10, 0, 0 );
	}
	if ( keyboard->getKeyState( "G" ) ) {
		_pos += Vector( 0, 0, -10 );
	}
	if ( keyboard->getKeyState( "H" ) ) {
		_pos += Vector( 10, 0, 0 );
	}
}

void TestObject::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawSphere( _pos * 0.001, 100 * 0.001, 50, 0xff0000, true );
}

void TestObject::onColliderEnter( ColliderConstPtr collider ) {
	if ( collider->getTag( ) == OBJECT_TAG_WALL ) {
		//_pos = _past_pos;
	}
}