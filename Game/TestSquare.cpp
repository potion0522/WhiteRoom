#include "TestSquare.h"

#include "Model.h"
#include "Drawer.h"


TestSquare::TestSquare( ) :
SquareCollider( _pos, Vector( 0, 0, -1 ), 1000, 1000, OBJECT_TAG_WALL ) {
	_model = ModelPtr( new Model );
	_model->alloc( 2 );
	_model->setTexture( Drawer::getTask( )->getImage( "Game/Texture/TextureWhite.png" ) );

	_pos = Vector( 2000, 0, 0 );
	Matrix rot = Matrix::makeTransformRotation( Vector( 0, -1, 0 ), PI * 0.5 );
	Vector vertex_pos[ 4 ] = {
		( Vector( -500,  500, 0 ) + _pos ) * 0.001,
		( Vector(  500,  500, 0 ) + _pos ) * 0.001,
		( Vector( -500, -500, 0 ) + _pos ) * 0.001,
		( Vector(  500, -500, 0 ) + _pos ) * 0.001,
	};

	Model::Vertex vertex[ 4 ] = {
		Model::Vertex( vertex_pos[ 0 ], 0, 0, Vector( -1, 0, 0 ) ),
		Model::Vertex( vertex_pos[ 1 ], 1, 0, Vector( -1, 0, 0 ) ),
		Model::Vertex( vertex_pos[ 2 ], 0, 1, Vector( -1, 0, 0 ) ),
		Model::Vertex( vertex_pos[ 3 ], 1, 1, Vector( -1, 0, 0 ) ),
	};

	_model->setVertex( 0, vertex[ 0 ] );
	_model->setVertex( 1, vertex[ 1 ] );
	_model->setVertex( 2, vertex[ 2 ] );

	_model->setVertex( 3, vertex[ 1 ] );
	_model->setVertex( 4, vertex[ 3 ] );
	_model->setVertex( 5, vertex[ 2 ] );
}

TestSquare::~TestSquare( ) {
}

void TestSquare::draw( ) const {
	_model->draw( );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawSphere( _pos + Vector( -1, 0, 0 ) * 0.5, 0.3, 30, 0x0000ff, true );
}

void TestSquare::onColliderEnter( ColliderConstPtr collider ) {
	int a = 0;
}