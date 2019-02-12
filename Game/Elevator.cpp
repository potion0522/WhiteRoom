#include "Elevator.h"
#include "define.h"

#include "Drawer.h"
#include "Model.h"
#include "Manager.h"

const char* ELEVATOR_TEXTURE = "Game/Texture/ElevatorTexture.png";
const int MOVE_TIME = 2000; // 2000ミリ秒で移動

Elevator::Elevator( const Vector& init_pos ) :
_pos( init_pos ),
_floor( FLOOR_GF ),
_moving( false ),
_starting_time( 0 ) {
	// モデルの作成
	generateElevator( );
}

Elevator::~Elevator( ) {
}

void Elevator::update( ) {
	// 呼ばれたいたら動く
	if ( _moving ) {
		move( );
	}
}

void Elevator::move( ) {
	int movement_floor = _floor - _past_floor;
	int distance = movement_floor * FLOOR_HEIGHT;

	int now_count = Manager::getInstance( )->getNowCount( );
	int moving_count = now_count - _starting_time;
	int move = distance / MOVE_TIME * moving_count;

	// 数字が低いほうがyが上なので符号を反転
	_pos.y = ( _past_floor * FLOOR_HEIGHT + move ) * -1;

	if ( MOVE_TIME < now_count - _starting_time ) {
		_pos.y = _floor * FLOOR_HEIGHT * -1;
		_moving = false;
	}
}

void Elevator::setMoveOrder( int order_floor ) {
	if ( _moving ) {
		return;
	}
	// 移動し初めの秒数(ミリ)を記録
	_starting_time = Manager::getInstance( )->getNowCount( );

	// 現在フロアとオーダーフロアを記録
	_past_floor = _floor;
	_floor = order_floor;
	_moving = true;
}

void Elevator::draw( ) const {
	_model->draw( _pos * MIRI_TO_METER_UNIT );
}

bool Elevator::isMoving( ) const {
	return _moving;
}

void Elevator::generateElevator( ) {
	_model = ModelPtr( new Model );

	const int NORMAL_WALL = 3;
	const int DOOR        = 2;
	const int OTHER_WALL  = 2; // 天井と床
	_model->alloc( ( NORMAL_WALL + DOOR + OTHER_WALL ) * 2 );

	_model->setTexture( Drawer::getTask( )->getImage( ELEVATOR_TEXTURE ) );

	{ // 通常壁
		Vector vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左上
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右上
			Vector( -ELEVATOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左下
			Vector(  ELEVATOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右下
		};

		for ( int i = 0; i < NORMAL_WALL; i++ ) {
			// 90度の回転行列
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 * i );

			Model::Vertex vertex[ 4 ] = {
				Model::Vertex( rot.multiply( vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
				Model::Vertex( rot.multiply( vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
				Model::Vertex( rot.multiply( vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
				Model::Vertex( rot.multiply( vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
			};

			int vertex_idx = i * 6;
			_model->setVertex( vertex_idx + 0, vertex[ 0 ] );
			_model->setVertex( vertex_idx + 1, vertex[ 1 ] );
			_model->setVertex( vertex_idx + 2, vertex[ 2 ] );

			_model->setVertex( vertex_idx + 3, vertex[ 1 ] );
			_model->setVertex( vertex_idx + 4, vertex[ 3 ] );
			_model->setVertex( vertex_idx + 5, vertex[ 2 ] );
		}
	}

	{ // 開閉するドア
		const double DOOR_WIDTH = ELEVATOR_WIDTH / 2;
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 * NORMAL_WALL );

		// 左側
		Vector left_door_vertex_pos[ 4 ] = {
			Vector( -DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左上
			Vector(           0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右上
			Vector( -DOOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左下
			Vector(           0,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex left_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};
		int vertex_idx = NORMAL_WALL * 6;
		_model->setVertex( vertex_idx + 0, left_door_vertex[ 0 ] );
		_model->setVertex( vertex_idx + 1, left_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 2, left_door_vertex[ 2 ] );

		_model->setVertex( vertex_idx + 3, left_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 4, left_door_vertex[ 3 ] );
		_model->setVertex( vertex_idx + 5, left_door_vertex[ 2 ] );


		// 右側
		Vector right_door_vertex_pos[ 4 ] = {
			Vector(          0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左上
			Vector( DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右上
			Vector(          0,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左下
			Vector( DOOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex right_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};
		vertex_idx = ( NORMAL_WALL + 1 ) * 6;
		_model->setVertex( vertex_idx + 0, right_door_vertex[ 0 ] );
		_model->setVertex( vertex_idx + 1, right_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 2, right_door_vertex[ 2 ] );

		_model->setVertex( vertex_idx + 3, right_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 4, right_door_vertex[ 3 ] );
		_model->setVertex( vertex_idx + 5, right_door_vertex[ 2 ] );
	}


	{ // 床と天井

		// 床
		Vector floor_vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, 0,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左上
			Vector(  ELEVATOR_WIDTH, 0,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右上
			Vector( -ELEVATOR_WIDTH, 0, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左下
			Vector(  ELEVATOR_WIDTH, 0, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex floor_vertex[ 4 ] = {
			Model::Vertex( floor_vertex_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( floor_vertex_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( floor_vertex_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( floor_vertex_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};
		int vertex_idx = ( NORMAL_WALL + DOOR ) * 6;
		_model->setVertex( vertex_idx + 0, floor_vertex[ 0 ] );
		_model->setVertex( vertex_idx + 1, floor_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 2, floor_vertex[ 2 ] );

		_model->setVertex( vertex_idx + 3, floor_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 4, floor_vertex[ 3 ] );
		_model->setVertex( vertex_idx + 5, floor_vertex[ 2 ] );
		

		// 天井
		Vector ceiling_vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左上
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右上
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左下
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex ceiling_vertex[ 4 ] = {
			Model::Vertex( ceiling_vertex_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( ceiling_vertex_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( ceiling_vertex_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( ceiling_vertex_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};
		vertex_idx = ( NORMAL_WALL + DOOR + 1 ) * 6;
		_model->setVertex( vertex_idx + 0, ceiling_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 1, ceiling_vertex[ 0 ] );
		_model->setVertex( vertex_idx + 2, ceiling_vertex[ 2 ] );

		_model->setVertex( vertex_idx + 3, ceiling_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 4, ceiling_vertex[ 2 ] );
		_model->setVertex( vertex_idx + 5, ceiling_vertex[ 3 ] );
	}
}
