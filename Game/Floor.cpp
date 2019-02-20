#include "Floor.h"
#include "define.h"
#include "Wall.h"
#include "CollideManager.h"

#include "Model.h"
#include "Mathematics.h"
#include "Drawer.h"

const char* ROOM_TEXTURE = "Game/Texture/FloorTexture.png";

Floor::Floor( CollideManagerPtr collide_manager, double y ) :
_y( y ) {
	// 部屋(壁・床)の生成
	generateFloor( );
	generateFloorCollider( );

	// 当たり判定をマネージャーに登録する
	setColliderToCollideManager( collide_manager );
}

Floor::~Floor( ) {
}

void Floor::draw( ) const {
	_floor->draw( );
}

double Floor::getY( ) const {
	return _y;
}

void Floor::generateFloor( ) {
	_floor = ModelPtr( new Model );

	const int NORMAL_WALL   = 3;
	const int ELEVATOR_WALL = 2;
	const int FLOOR_NUM     = 1;
	_floor->alloc( ( NORMAL_WALL + ELEVATOR_WALL + FLOOR_NUM ) * 2 );

	_floor->setTexture( Drawer::getTask( )->getImage( ROOM_TEXTURE ) );

	{ // 壁3枚
		Vector vertex_pos[ 4 ] = {
			Vector( -FLOOR_WIDTH / 2, _y + FLOOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 左上
			Vector(  FLOOR_WIDTH / 2, _y + FLOOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 右上
			Vector( -FLOOR_WIDTH / 2, _y +            0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 左下
			Vector(  FLOOR_WIDTH / 2, _y +            0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 右下
		};						 

		for ( int i = 0; i < NORMAL_WALL; i++ ) {
			// 90度の回転行列
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * i );

			Model::Vertex vertex[ 4 ] = {
				Model::Vertex( rot.multiply( vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
				Model::Vertex( rot.multiply( vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
				Model::Vertex( rot.multiply( vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
				Model::Vertex( rot.multiply( vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
			};

			int vertex_idx = i * 6;
			_floor->setVertex( vertex_idx + 0, vertex[ 0 ] );
			_floor->setVertex( vertex_idx + 1, vertex[ 1 ] );
			_floor->setVertex( vertex_idx + 2, vertex[ 2 ] );

			_floor->setVertex( vertex_idx + 3, vertex[ 1 ] );
			_floor->setVertex( vertex_idx + 4, vertex[ 3 ] );
			_floor->setVertex( vertex_idx + 5, vertex[ 2 ] );
		}
	}



	{ // エレベーターのある壁
		const double WALL_WIDTH = ( FLOOR_WIDTH / 2 - ELEVATOR_WIDTH );

		// 270度の回転行列(壁が4枚なので)
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * NORMAL_WALL );

		// 左側
		Vector left_side_vertex_pos[ 4 ] = {
			Vector( -FLOOR_WIDTH / 2             , _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 左上
			Vector( -FLOOR_WIDTH / 2 + WALL_WIDTH, _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 右上
			Vector( -FLOOR_WIDTH / 2             , _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 左下
			Vector( -FLOOR_WIDTH / 2 + WALL_WIDTH, _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex left_side_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};

		int vertex_idx = NORMAL_WALL * 6;
		_floor->setVertex( vertex_idx + 0, left_side_vertex[ 0 ] );
		_floor->setVertex( vertex_idx + 1, left_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 2, left_side_vertex[ 2 ] );

		_floor->setVertex( vertex_idx + 3, left_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 4, left_side_vertex[ 3 ] );
		_floor->setVertex( vertex_idx + 5, left_side_vertex[ 2 ] );


		// 右側
		Vector right_side_vertex_pos[ 4 ] = {
			Vector( FLOOR_WIDTH / 2 - WALL_WIDTH, _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 左上
			Vector( FLOOR_WIDTH / 2             , _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 右上
			Vector( FLOOR_WIDTH / 2 - WALL_WIDTH, _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 左下
			Vector( FLOOR_WIDTH / 2             , _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex right_side_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};

		vertex_idx = ( NORMAL_WALL + 1 ) * 6;
		_floor->setVertex( vertex_idx + 0, right_side_vertex[ 0 ] );
		_floor->setVertex( vertex_idx + 1, right_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 2, right_side_vertex[ 2 ] );

		_floor->setVertex( vertex_idx + 3, right_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 4, right_side_vertex[ 3 ] );
		_floor->setVertex( vertex_idx + 5, right_side_vertex[ 2 ] );
	}




	{ // 床
		Model::Vertex vertex[ 4 ] = {
			Model::Vertex( Vector( -FLOOR_WIDTH / 2, _y,  FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( Vector(  FLOOR_WIDTH / 2, _y,  FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( Vector( -FLOOR_WIDTH / 2, _y, -FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( Vector(  FLOOR_WIDTH / 2, _y, -FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};


		int vertex_idx = ( NORMAL_WALL + ELEVATOR_WALL ) * 6;
		_floor->setVertex( vertex_idx + 0, vertex[ 0 ] );
		_floor->setVertex( vertex_idx + 1, vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 2, vertex[ 2 ] );

		_floor->setVertex( vertex_idx + 3, vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 4, vertex[ 3 ] );
		_floor->setVertex( vertex_idx + 5, vertex[ 2 ] );
	}
}

void Floor::generateFloorCollider( ) {
	{ // 通常壁の当たり判定
		Vector norm = Vector( 0, 0, -1 );
		Vector pos  = Vector( 0, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 );

		for ( int i = 0; i < NORMAL_WALL_NUM; i++ ) {
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * i );
			Vector pos_  = rot.multiply( pos );
			Vector norm_ = rot.multiply( norm );
			_wall_colliders[ i ] = WallPtr( new Wall( pos_, norm_, FLOOR_WIDTH, FLOOR_HEIGHT ) );
		}
	}
	
	{ // エレベーターのある壁の当たり判定
		const double SIDE_WALL_WIDTH     = ( FLOOR_WIDTH - ELEVATOR_WIDTH * 2 ) / 2;
		const double ELEVATOR_WALL_WIDTH = ELEVATOR_WIDTH;

		Vector norm = Vector( 0, 0, -1 );
		Vector pos[ ELEVATOR_SIDE_WALL_NUM ] = {
			Vector( -FLOOR_WIDTH / 2, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 ) + Vector( SIDE_WALL_WIDTH / 2, 0, 0 ),
			Vector(                0, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 ),
			Vector(  FLOOR_WIDTH / 2, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 ) - Vector( SIDE_WALL_WIDTH / 2, 0, 0 ),
		};

		// 270度回転
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * 3 );
		for ( int i = 0; i < ELEVATOR_SIDE_WALL_NUM; i++ ) {
			pos[ i ] = rot.multiply( pos[ i ] );
		}
		norm = rot.multiply( norm );

		// 回転した座標で当たり判定を生成
		_wall_colliders[ NORMAL_WALL_NUM + 0 ] = WallPtr( new Wall( pos[ 0 ], norm,     SIDE_WALL_WIDTH, FLOOR_HEIGHT ) );
		_wall_colliders[ NORMAL_WALL_NUM + 1 ] = WallPtr( new Wall( pos[ 1 ], norm, ELEVATOR_WALL_WIDTH, FLOOR_HEIGHT ) );
		_wall_colliders[ NORMAL_WALL_NUM + 2 ] = WallPtr( new Wall( pos[ 2 ], norm,     SIDE_WALL_WIDTH, FLOOR_HEIGHT ) );
	}
}

void Floor::setColliderToCollideManager( CollideManagerPtr collide_manager ) {
	// 壁
	for ( int i = 0; i < NORMAL_WALL_NUM + ELEVATOR_SIDE_WALL_NUM; i++ ) {
		collide_manager->addStaticCollider( _wall_colliders[ i ] );
	}
}