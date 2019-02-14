#include "Elevator.h"
#include "define.h"

#include "Drawer.h"
#include "Model.h"
#include "Manager.h"

const char* ELEVATOR_TEXTURE = "Game/Texture/ElevatorTexture.png";
const int ELEVATOR_MOVE_TIME = 2000; // �~���b
const int DOOR_ANIM_TIME = 1000; // �~���b
const int MAX_DOOR_MOVE_LENGTH = ELEVATOR_WIDTH;

Elevator::Elevator( const Vector& init_pos ) :
_elevator_pos( init_pos ),
_door_open_length( MAX_DOOR_MOVE_LENGTH ),
_floor( FLOOR_GF ),
_state( ELEVATOR_STATE_IDLE ),
_starting_time( 0 ) {
	// ���f���̍쐬
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

	// ���݃t���A�ƃI�[�_�[�t���A���L�^
	_past_floor = _floor;
	_floor = order_floor;
	_state = ELEVATOR_STATE_CLOSING;
	_starting_time = getNowCount( );
}

void Elevator::draw( ) const {
	// �G���x�[�^�[���[���̕`��
	_elevator_room->draw( _elevator_pos * MIRI_TO_METER_UNIT );

	// �h�A�̊J����(�h�A�̊J��z��)
	Vector door_open = Vector( 0, 0, _door_open_length );

	// �h�A�̕`��
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

	// �������Ⴂ�ق���y����Ȃ̂ŕ����𔽓]
	_elevator_pos.y = ( _past_floor * FLOOR_HEIGHT + move ) * -1;

	// ����
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

	// �h�A�̊J������ݒ�
	_door_open_length = move;

	// �J���؂�����ҋ@
	if ( DOOR_ANIM_TIME < moving_count ) {
		_state = ELEVATOR_STATE_IDLE;
	}
}

void Elevator::actOnClosing( ) {
	int distance = MAX_DOOR_MOVE_LENGTH;

	int now_count = getNowCount( );
	int moving_count = now_count - _starting_time;
	double move = distance / ( double )DOOR_ANIM_TIME * moving_count;

	// �h�A�̊J������ݒ�
	_door_open_length = MAX_DOOR_MOVE_LENGTH - move;

	// �ߐ؂�����ړ�
	if ( DOOR_ANIM_TIME < moving_count ) {
		_state = ELEVATOR_STATE_MOVING;
		_starting_time = getNowCount( );
	}
}

void Elevator::generateElevator( ) {
	_elevator_room = ModelPtr( new Model );

	const int NORMAL_WALL = 3;
	const int OTHER_WALL  = 2; // �V��Ə�
	_elevator_room->alloc( ( NORMAL_WALL + OTHER_WALL ) * 2 );

	_elevator_room->setTexture( Drawer::getTask( )->getImage( ELEVATOR_TEXTURE ) );

	// �ʏ��
	// --------------------------------------------------------------------------- //
	{ 
		Vector vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -ELEVATOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
		};

		for ( int i = 0; i < NORMAL_WALL; i++ ) {
			// 90�x�̉�]�s��
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 * i );

			Model::Vertex vertex[ 4 ] = {
				Model::Vertex( rot.multiply( vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
				Model::Vertex( rot.multiply( vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
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

	// ���ƓV��
	// --------------------------------------------------------------------------- //
	{ 
		// ��
		Vector floor_vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, 0,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH, 0,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -ELEVATOR_WIDTH, 0, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH, 0, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
		};
		Model::Vertex floor_vertex[ 4 ] = {
			Model::Vertex( floor_vertex_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( floor_vertex_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( floor_vertex_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( floor_vertex_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		int vertex_idx = NORMAL_WALL * 6;
		_elevator_room->setVertex( vertex_idx + 0, floor_vertex[ 0 ] );
		_elevator_room->setVertex( vertex_idx + 1, floor_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 2, floor_vertex[ 2 ] );

		_elevator_room->setVertex( vertex_idx + 3, floor_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 4, floor_vertex[ 3 ] );
		_elevator_room->setVertex( vertex_idx + 5, floor_vertex[ 2 ] );
		

		// �V��
		Vector ceiling_vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT,  ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT, -ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
		};
		Model::Vertex ceiling_vertex[ 4 ] = {
			Model::Vertex( ceiling_vertex_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( ceiling_vertex_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( ceiling_vertex_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( ceiling_vertex_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		vertex_idx = ( NORMAL_WALL + 1 ) * 6;
		_elevator_room->setVertex( vertex_idx + 0, ceiling_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 1, ceiling_vertex[ 0 ] );
		_elevator_room->setVertex( vertex_idx + 2, ceiling_vertex[ 2 ] );

		_elevator_room->setVertex( vertex_idx + 3, ceiling_vertex[ 1 ] );
		_elevator_room->setVertex( vertex_idx + 4, ceiling_vertex[ 2 ] );
		_elevator_room->setVertex( vertex_idx + 5, ceiling_vertex[ 3 ] );
	}

	// �J����h�A
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

		// �E��
		Vector right_door_vertex_pos[ 4 ] = {
			Vector( -DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(           0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -DOOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector(           0,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
		};
		Model::Vertex right_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		int vertex_idx = 0;
		_elevator_door_right->setVertex( 0, right_door_vertex[ 0 ] );
		_elevator_door_right->setVertex( 1, right_door_vertex[ 1 ] );
		_elevator_door_right->setVertex( 2, right_door_vertex[ 2 ] );

		_elevator_door_right->setVertex( 3, right_door_vertex[ 1 ] );
		_elevator_door_right->setVertex( 4, right_door_vertex[ 3 ] );
		_elevator_door_right->setVertex( 5, right_door_vertex[ 2 ] );


		// ����
		Vector left_door_vertex_pos[ 4 ] = {
			Vector(          0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector( DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
			Vector(          0,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // ����
			Vector( DOOR_WIDTH,               0, ELEVATOR_WIDTH ) * MIRI_TO_METER_UNIT, // �E��
		};
		Model::Vertex left_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		_elevator_door_left->setVertex( 0, left_door_vertex[ 0 ] );
		_elevator_door_left->setVertex( 1, left_door_vertex[ 1 ] );
		_elevator_door_left->setVertex( 2, left_door_vertex[ 2 ] );
										 
		_elevator_door_left->setVertex( 3, left_door_vertex[ 1 ] );
		_elevator_door_left->setVertex( 4, left_door_vertex[ 3 ] );
		_elevator_door_left->setVertex( 5, left_door_vertex[ 2 ] );
	}
}
