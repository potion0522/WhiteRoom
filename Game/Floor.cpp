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

	// 当たり判定
	Vector pos[ WALL_NUM ] = {
		Vector(                0, _y + FLOOR_HEIGHT / 2,                           FLOOR_WIDTH / 2 ), // 正面
		Vector( -FLOOR_WIDTH / 2, _y + FLOOR_HEIGHT / 2,                                         0 ), // 左
		Vector(                0, _y + FLOOR_HEIGHT / 2,                          -FLOOR_WIDTH / 2 ), // 後ろ
		Vector(  FLOOR_WIDTH / 2, _y + FLOOR_HEIGHT / 2,  ( FLOOR_WIDTH / 2 - ( FLOOR_WIDTH / 2 - ELEVATOR_WIDTH ) / 2 ) ), // 右
		Vector(  FLOOR_WIDTH / 2, _y + FLOOR_HEIGHT / 2, -( FLOOR_WIDTH / 2 - ( FLOOR_WIDTH / 2 - ELEVATOR_WIDTH ) / 2 ) ), // 右																	 // 右
	};

	Vector norms[ WALL_NUM ] = {
		Vector(  0,  0, -1 ), // 正面
		Vector(  1,  0,  0 ), // 左
		Vector(  0,  0,  1 ), // 後ろ
		Vector( -1,  0,  0 ), // 右
		Vector( -1,  0,  0 ), // 右
	};
	for ( int i = 0; i < WALL_NUM; i++ ) {
		double width = FLOOR_WIDTH;
		// エレベーターのある面の壁
		if ( i == WALL_NUM - 1 || i == WALL_NUM - 2 ) {
			width = FLOOR_WIDTH / 2 - ELEVATOR_WIDTH;
		}

		_wall_colliders[ i ] = WallPtr( new Wall( 
			pos  [ i ], // pos
			norms[ i ], // norm
			width, // width
			FLOOR_HEIGHT // height
		) );

		collide_manager->addStaticCollider( _wall_colliders[ i ] );
	}
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