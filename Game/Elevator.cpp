#include "Elevator.h"
#include "define.h"

#include "Drawer.h"
#include "Model.h"
#include "Manager.h"

const char* ELEVATOR_TEXTURE = "Game/Texture/ElevatorTexture.png";
const int ELEVATOR_MOVE_TIME = 2000; // ミリ秒
const int DOOR_ANIM_TIME = 1000; // ミリ秒
const int MAX_DOOR_MOVE_LENGTH = ELEVATOR_WIDTH;

Elevator::Elevator( const Vector& init_pos ) :
_elevator_pos( init_pos ),
_door_open_length( MAX_DOOR_MOVE_LENGTH ),
_floor( FLOOR_GF ),
_state( ELEVATOR_STATE_IDLE ),
_starting_time( 0 ) {
	// モデルの作成
	generateElevator( );
}

Elevator::~Elevator( ) {
}

void Elevator::update( ) {
	switch ( _state ) {
		case ELEVATOR_STATE_IDLE:
			actOnIdle( );
			break;
		case ELEVATOR_STATE_MOVING:
			actOnMoving( );
			break;
		case ELEVATOR_STATE_OPENING:
			actOnOpening( );
			break;
		case ELEVATOR_STATE_CLOSING:
			actOnClosing( );
			break;
	}
}

void Elevator::setMoveOrder( int order_floor ) {
	if ( !isItPossibleToOrderElevator( ) ) {
		return;
	}

	// 現在フロアとオーダーフロアを記録
	_past_floor = _floor;
	_floor = order_floor;
	_state = ELEVATOR_STATE_CLOSING;
	_starting_time = getNowCount( );
}

void Elevator::draw( ) const {
	// エレベータールームの描画
	_elevator_room->draw( _elevator_pos * MIRI_TO_METER_UNIT );

	// ドアの開閉距離(ドアの開閉はz軸)
	Vector door_open = Vector( 0, 0, _door_open_length );

	// ドアの描画
	Manager* manager = Manager::getInstance( );
	manager->setUseBackCulling( false );
	_elevator_door_left->draw ( ( _elevator_pos + door_open ) * MIRI_TO_METER_UNIT );
	_elevator_door_right->draw( ( _elevator_pos - door_open ) * MIRI_TO_METER_UNIT );
	manager->setUseBackCulling( true );
}


bool Elevator::isItPossibleToOrderElevator( ) const {
	return ( _state == ELEVATOR_STATE_IDLE );
}

int Elevator::getNowCount( ) const {
	return Manager::getInstance( )->getNowCount( );
}


void Elevator::actOnIdle( ) {
}

void Elevator::actOnMoving( ) {
	int movement_floor = _floor - _past_floor;
	int distance = movement_floor * FLOOR_HEIGHT;

	int now_count = getNowCount( );
	int moving_count = now_count - _starting_time;
	double move = distance / ( double )ELEVATOR_MOVE_TIME * moving_count;

	// 数字が低いほうがyが上なので符号を反転
	_elevator_pos.y = ( _past_floor * FLOOR_HEIGHT + move ) * -1;

	// 到着
	if ( ELEVATOR_MOVE_TIME < moving_count ) {
		_elevator_pos.y = _floor * FLOOR_HEIGHT * -1;
		_state = ELEVATOR_STATE_OPENING;
		_starting_time = getNowCount( );
	}
}

void Elevator::actOnOpening( ) {
	int distance = MAX_DOOR_MOVE_LENGTH;

	int now_count = getNowCount( );
	int moving_count = now_count - _starting_time;
	double move = distance / ( double )DOOR_ANIM_TIME * moving_count;

	// ドアの開閉距離を設定
	_door_open_length = move;

	// 開け切ったら待機
	if ( DOOR_ANIM_TIME < moving_count ) {
		_state = ELEVATOR_STATE_IDLE;
	}
}

void Elevator::actOnClosing( ) {
	int distance = MAX_DOOR_MOVE_LENGTH;

	int now_count = getNowCount( );
	int moving_count = now_count - _starting_time;
	double move = distance / ( double )DOOR_ANIM_TIME * moving_count;

	// ドアの開閉距離を設定
	_door_open_length = MAX_DOOR_MOVE_LENGTH - move;

	// 閉め切ったら移動
	if ( DOOR_ANIM_TIME < moving_count ) {
		_state = ELEVATOR_STATE_MOVING;
		_starting_time = getNowCount( );
	}
}

void Elevator::generateElevator( ) {
	_elevator_room = ModelPtr( new Model );

	const int NORMAL_WALL = 3;
	const int OTHER_WALL  = 2; // 天井と床
	_elevator_room->alloc( ( NORMAL_WALL + OTHER_WALL ) * 2 );

	_elevator_room->setTexture( Drawer::getTask( )->getImage( ELEVATOR_TEXTURE ) );

	// 通常壁
	// --------------------------------------------------------------------------- //
	{ 
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
			_elevator_room->setVertex( vertex_idx + 0, vertex[ 0 ] );
			_elevator_room->setVertex( vertex_idx + 1, vertex[ 1 ] );
			_elevator_room->setVertex( vertex_idx + 2, vertex[ 2 ] );

			_elevator_room->setVertex( vertex_idx + 3, vertex[ 1 ] );
			_elevator_room->setVertex( vertex_idx + 4, vertex[ 3 ] );
			_elevator_room->setVertex( vertex_idx + 5, vertex[ 2 ] );
		}
	}

	// 床と天井
	// --------------------------------------------------------------------------- //
	{ 
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
		int vertex_idx = NORMAL_WALL * 6;
		_elevator_room->setVertex( vertex_idx + 0, floor_vertex[ 0 ] );
		_elevator_room->setVertex( vertex_idx + 1, floor_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 2, floor_vertex[ 2 ] );

		_elevator_room->setVertex( vertex_idx + 3, floor_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 4, floor_vertex[ 3 ] );
		_elevator_room->setVertex( vertex_idx + 5, floor_vertex[ 2 ] );
		

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
		vertex_idx = ( NORMAL_WALL + 1 ) * 6;
		_elevator_room->setVertex( vertex_idx + 0, ceiling_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 1, ceiling_vertex[ 0 ] );
		_elevator_room->setVertex( vertex_idx + 2, ceiling_vertex[ 2 ] );

		_elevator_room->setVertex( vertex_idx + 3, ceiling_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 4, ceiling_vertex[ 2 ] );
		_elevator_room->setVertex( vertex_idx + 5, ceiling_vertex[ 3 ] );
	}

	// 開閉するドア
	// --------------------------------------------------------------------------- //
	_elevator_door_left = ModelPtr( new Model );
	_elevator_door_left->alloc( 2 );
	_elevator_door_left->setTexture( Drawer::getTask( )->getImage( ELEVATOR_TEXTURE ) );
	
	_elevator_door_right = ModelPtr( new Model );
	_elevator_door_right->alloc( 2 );
	_elevator_door_right->setTexture( Drawer::getTask( )->getImage( ELEVATOR_TEXTURE ) );

	{
		const double DOOR_WIDTH = ELEVATOR_WIDTH;
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 * NORMAL_WALL );

		// 右側
		Vector right_door_vertex_pos[ 4 ] = {
			Vector( -DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左上
			Vector(           0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右上
			Vector( -DOOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左下
			Vector(           0,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex right_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};
		int vertex_idx = 0;
		_elevator_door_right->setVertex( 0, right_door_vertex[ 0 ] );
		_elevator_door_right->setVertex( 1, right_door_vertex[ 1 ] );
		_elevator_door_right->setVertex( 2, right_door_vertex[ 2 ] );

		_elevator_door_right->setVertex( 3, right_door_vertex[ 1 ] );
		_elevator_door_right->setVertex( 4, right_door_vertex[ 3 ] );
		_elevator_door_right->setVertex( 5, right_door_vertex[ 2 ] );


		// 左側
		Vector left_door_vertex_pos[ 4 ] = {
			Vector(          0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左上
			Vector( DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右上
			Vector(          0,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 左下
			Vector( DOOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // 右下
		};
		Model::Vertex left_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // 左上
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // 右上
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // 左下
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // 右下
		};
		_elevator_door_left->setVertex( 0, left_door_vertex[ 0 ] );
		_elevator_door_left->setVertex( 1, left_door_vertex[ 1 ] );
		_elevator_door_left->setVertex( 2, left_door_vertex[ 2 ] );
										 
		_elevator_door_left->setVertex( 3, left_door_vertex[ 1 ] );
		_elevator_door_left->setVertex( 4, left_door_vertex[ 3 ] );
		_elevator_door_left->setVertex( 5, left_door_vertex[ 2 ] );
	}
}
