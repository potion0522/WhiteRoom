#include "Room.h"
#include "define.h"

#include "Model.h"
#include "Mathematics.h"
#include "Drawer.h"

const char* ROOM_TEXTURE = "Game/Texture/RoomTexture.png";

Room::Room( double y ) :
_y( y ) {
	_room = ModelPtr( new Model );

	const int WALL_NUM  = 4;
	const int FLOOR_NUM = 1;
	_room->alloc( ( WALL_NUM + FLOOR_NUM ) * 2 );

	_room->setTexture( Drawer::getTask( )->getImage( ROOM_TEXTURE ) );

	Vector vertex_pos[ 4 ] = {
		Vector( -ROOM_WIDTH, _y + ROOM_HEIGHT, ROOM_DEPTH ), // 左上
		Vector(  ROOM_WIDTH, _y + ROOM_HEIGHT, ROOM_DEPTH ), // 右上
		Vector( -ROOM_WIDTH, _y +           0, ROOM_DEPTH ), // 左下
		Vector(  ROOM_WIDTH, _y +           0, ROOM_DEPTH ), // 右下
	};

	// 壁
	for ( int i = 0; i < WALL_NUM; i++ ) {
		// 90度の回転行列
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.25 * i );

		Model::Vertex vertex[ 4 ] = {
			Model::Vertex( rot.multiply( vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( rot.multiply( vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( rot.multiply( vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( rot.multiply( vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};

		int vertex_idx = i * 6;
		_room->setVertex( vertex_idx + 0, vertex[ 0 ] );
		_room->setVertex( vertex_idx + 1, vertex[ 1 ] );
		_room->setVertex( vertex_idx + 2, vertex[ 2 ] );

		_room->setVertex( vertex_idx + 3, vertex[ 1 ] );
		_room->setVertex( vertex_idx + 4, vertex[ 3 ] );
		_room->setVertex( vertex_idx + 5, vertex[ 2 ] );
	}

	// 床
	Model::Vertex vertex[ 4 ] = {
		Model::Vertex( Vector( -ROOM_WIDTH, _y,  ROOM_DEPTH ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
		Model::Vertex( Vector(  ROOM_WIDTH, _y,  ROOM_DEPTH ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
		Model::Vertex( Vector( -ROOM_WIDTH, _y, -ROOM_DEPTH ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
		Model::Vertex( Vector(  ROOM_WIDTH, _y, -ROOM_DEPTH ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
	};

	int vertex_idx = WALL_NUM * 6;
	_room->setVertex( vertex_idx + 0, vertex[ 0 ] );
	_room->setVertex( vertex_idx + 1, vertex[ 1 ] );
	_room->setVertex( vertex_idx + 2, vertex[ 2 ] );

	_room->setVertex( vertex_idx + 3, vertex[ 1 ] );
	_room->setVertex( vertex_idx + 4, vertex[ 3 ] );
	_room->setVertex( vertex_idx + 5, vertex[ 2 ] );
}

Room::~Room( ) {
}

void Room::draw( ) const {
	_room->draw( );
}

double Room::getY( ) const {
	return _y;
}