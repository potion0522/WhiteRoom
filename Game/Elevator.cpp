#include "Elevator.h"
#include "define.h"
#include "ElevatorAnnounce.h"
#include "Wall.h"
#include "Door.h"
#include "CollideManager.h"
#include "ElevatorButton.h"
#include "ElevatorBox.h"

#include "Drawer.h"
#include "Model.h"
#include "Manager.h"

const char* ELEVATOR_TEXTURE = "Game/Texture/ElevatorTexture.png";
const char* ELEVATOR_WALL_TEXTURE = "Game/Texture/WallTexture.png";
const int ELEVATOR_MOVE_TIME = 2000; // �~���b
const int DOOR_ANIM_TIME = 1000; // �~���b
const int MAX_DOOR_MOVE_LENGTH = ELEVATOR_WIDTH / 2;

Elevator::Elevator( const Vector& init_pos, CollideManagerPtr collide_manager ) :
SphereCollider( _sphere_collider_pos, ELEVATOR_WIDTH / 2, OBJECT_TAG_ELEVATOR ),
_pos( init_pos ),
_sphere_collider_pos( _pos + Vector( 0, ELEVATOR_HEIGHT / 2, 0 ) ),
_door_open_length( MAX_DOOR_MOVE_LENGTH ),
_floor( ELEVATOR_INIT_FLOOR ),
_state( ELEVATOR_STATE_IDLE ),
_starting_time( 0 ) {
	// �ʒm�@�\�̃C���X�^���X
	_announce = ElevatorAnnouncePtr( new ElevatorAnnounce );
	
	// �O������̃A�N�Z�X�p�N���X�̃C���X�^���X
	_elevator_button = ElevatorButtonPtr( new ElevatorButton( [ & ]( FLOOR floor ) { requestMoveElevatorButtonToElevator( floor ); } ) );
	_elevator_box    = ElevatorBoxPtr   ( new ElevatorBox( [ & ]( Vector* obj_pos ) { requextRideElevatorBoxToElevator( obj_pos ); } ) );

	// ���f���̍쐬
	generateElevator( );
	generateElevatorCollider( );

	// �o�^
	for ( int i = 0; i < WALL_COLLIDER_NUM; i++ ) {
		collide_manager->addStaticCollider( _wall_colliders[ i ] );
	}
	collide_manager->addStaticCollider( _door_collider );
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
	_sphere_collider_pos = _pos + Vector( 0, ELEVATOR_HEIGHT / 2, 0 );
	_ride_obj.clear( );
}

ElevatorAnnounceObservablePtr Elevator::getAnnounceObservable( ) const {
	return _announce;
}

ElevatorButtonPtr Elevator::getElevatorButton( ) const {
	return _elevator_button;
}

ElevatorBoxPtr Elevator::getElevatorBox( ) const {
	return _elevator_box;
}

void Elevator::draw( ) const {
	{ // �o�b�N�J�����O��؂�
		Manager* manager = Manager::getInstance( );
		manager->setUseBackCulling( false );

		// �G���x�[�^�[���[���̕`��
		_elevator_room->draw( _pos * MIRI_TO_METER_UNIT );

		// �h�A�̊J����(�h�A�̊J��z��)
		Vector door_open = Vector( 0, 0, _door_open_length );

		// �h�A�̕`��
		_elevator_door_left->draw ( ( _pos + door_open ) * MIRI_TO_METER_UNIT );
		_elevator_door_right->draw( ( _pos - door_open ) * MIRI_TO_METER_UNIT );

		// �G���x�[�^�[���ړ������
		_elevator_wall->draw( Vector( _pos.x + ELEVATOR_WALL_OVER_SIZE / 2, 0, _pos.z ) * MIRI_TO_METER_UNIT );

		manager->setUseBackCulling( true );
	}
}

void Elevator::requestMoveElevatorButtonToElevator( FLOOR order ) {
	if ( !isItPossibleToOrderElevator( ) ) {
		return;
	}

	// ���݃t���A�ƃI�[�_�[�t���A���L�^
	_past_floor = _floor;
	_floor = ( FLOOR )order;
	_state = ELEVATOR_STATE_CLOSING;
	_starting_time = getNowCount( );
	
	// �ʒm
	_announce->announceMove( );

	// �h�A�̔��������
	_door_collider->setEnabled( true );
}

void Elevator::requextRideElevatorBoxToElevator( Vector* obj_pos ) {
	_ride_obj.push_back( obj_pos );
}

bool Elevator::isItPossibleToOrderElevator( ) const {
	return ( _state == ELEVATOR_STATE_IDLE );
}

int Elevator::getNowCount( ) const {
	return Manager::getInstance( )->getNowCount( );
}


void Elevator::actOnIdle( ) {
	_door_collider->setEnabled( false );
}

void Elevator::actOnMoving( ) {
	int movement_floor = _floor - _past_floor;
	int distance = movement_floor * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT;

	int now_count = getNowCount( );
	int moving_count = now_count - _starting_time;
	double move = distance / ( double )ELEVATOR_MOVE_TIME * moving_count;

	// �������Ⴂ�ق���y����Ȃ̂ŕ����𔽓]
	_pos.y = ( _past_floor * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT + move ) * -1;

	// ����Ă���I�u�W�F�N�g��y��ύX
	for ( int i = 0; i < _ride_obj.size( ); i++ ) {
		_ride_obj[ i ]->y = _pos.y;
	}

	// ����
	if ( ELEVATOR_MOVE_TIME < moving_count ) {
		_pos.y = _floor * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * -1;
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

		// �ʒm
		_announce->announceArrive( _floor );
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
	DrawerPtr drawer = Drawer::getTask( );
	_elevator_room = ModelPtr( new Model );

	const int NORMAL_WALL = 3;
	const int OTHER_WALL  = 2; // �V��Ə�
	_elevator_room->alloc( ( NORMAL_WALL + OTHER_WALL ) * 2 );

	_elevator_room->setTexture( drawer->getImage( ELEVATOR_TEXTURE ) );

	// �����̕�
	// --------------------------------------------------------------------------- //
	{ 
		Vector vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH / 2, ELEVATOR_HEIGHT, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH / 2, ELEVATOR_HEIGHT, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -ELEVATOR_WIDTH / 2,               0, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH / 2,               0, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
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
			Vector( -ELEVATOR_WIDTH / 2, 0,  ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH / 2, 0,  ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -ELEVATOR_WIDTH / 2, 0, -ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(  ELEVATOR_WIDTH / 2, 0, -ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
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
		Vector height = Vector( 0, ELEVATOR_HEIGHT, 0 ) * MIRI_TO_METER_UNIT;
		Model::Vertex ceiling_vertex[ 4 ] = {
			Model::Vertex( floor_vertex_pos[ 0 ] + height, 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( floor_vertex_pos[ 1 ] + height, 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( floor_vertex_pos[ 2 ] + height, 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( floor_vertex_pos[ 3 ] + height, 1, 1, Vector( 0, 1, 0 ) ), // �E��
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
	_elevator_door_left->setTexture( drawer->getImage( ELEVATOR_TEXTURE ) );
	
	_elevator_door_right = ModelPtr( new Model );
	_elevator_door_right->alloc( 2 );
	_elevator_door_right->setTexture( drawer->getImage( ELEVATOR_TEXTURE ) );

	{
		const double DOOR_WIDTH = ELEVATOR_WIDTH / 2 + 200;
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 * NORMAL_WALL );

		// �E��
		Vector right_door_vertex_pos[ 4 ] = {
			Vector( -DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(           0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -DOOR_WIDTH,               0, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(           0,               0, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
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
			Vector(          0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector( DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			Vector(          0,               0, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector( DOOR_WIDTH,               0, ELEVATOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
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
	
	// �G���x�[�^�[���ړ������
	// --------------------------------------------------------------------------- //
	_elevator_wall = ModelPtr( new Model );
	_elevator_wall->alloc( ( NORMAL_WALL + 2 ) * 2 );
	_elevator_wall->setTexture( drawer->getImage( ELEVATOR_WALL_TEXTURE ) );
	{ // ��
		const double WIDTH = ELEVATOR_WIDTH + ELEVATOR_WALL_OVER_SIZE;
		const double HEIGHT = FLOOR_HEIGHT - ( MAX_FLOOR * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT );
		{
			Vector vertex_pos[ 4 ] = {
				Vector( -WIDTH / 2, FLOOR_HEIGHT + ELEVATOR_WALL_OVER_SIZE, WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
				Vector(  WIDTH / 2, FLOOR_HEIGHT + ELEVATOR_WALL_OVER_SIZE, WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
				Vector( -WIDTH / 2,       HEIGHT - ELEVATOR_WALL_OVER_SIZE, WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
				Vector(  WIDTH / 2,       HEIGHT - ELEVATOR_WALL_OVER_SIZE, WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
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
				_elevator_wall->setVertex( vertex_idx + 0, vertex[ 0 ] );
				_elevator_wall->setVertex( vertex_idx + 1, vertex[ 1 ] );
				_elevator_wall->setVertex( vertex_idx + 2, vertex[ 2 ] );

				_elevator_wall->setVertex( vertex_idx + 3, vertex[ 1 ] );
				_elevator_wall->setVertex( vertex_idx + 4, vertex[ 3 ] );
				_elevator_wall->setVertex( vertex_idx + 5, vertex[ 2 ] );
			}
		}

		{ // �V��Ə�
			Vector vertex_pos[ 4 ] = {
				Vector( -WIDTH / 2, HEIGHT,  WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
				Vector(  WIDTH / 2, HEIGHT,  WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
				Vector( -WIDTH / 2, HEIGHT, -WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
				Vector(  WIDTH / 2, HEIGHT, -WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			};
			Vector over_size = Vector( 0, ELEVATOR_WALL_OVER_SIZE, 0 ) * MIRI_TO_METER_UNIT;

			// ��
			Model::Vertex floor_vertex[ 4 ] = {
				Model::Vertex( vertex_pos[ 0 ] - over_size, 0, 0, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( vertex_pos[ 1 ] - over_size, 1, 0, Vector( 0, 1, 0 ) ), // �E��
				Model::Vertex( vertex_pos[ 2 ] - over_size, 0, 1, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( vertex_pos[ 3 ] - over_size, 1, 1, Vector( 0, 1, 0 ) ), // �E��
			};
			int vertex_idx = ( NORMAL_WALL * 6 );
			_elevator_wall->setVertex( vertex_idx + 0, floor_vertex[ 0 ] );
			_elevator_wall->setVertex( vertex_idx + 1, floor_vertex[ 1 ] );
			_elevator_wall->setVertex( vertex_idx + 2, floor_vertex[ 2 ] );

			_elevator_wall->setVertex( vertex_idx + 3, floor_vertex[ 1 ] );
			_elevator_wall->setVertex( vertex_idx + 4, floor_vertex[ 3 ] );
			_elevator_wall->setVertex( vertex_idx + 5, floor_vertex[ 2 ] );
		

			// �V��
			for ( int i = 0; i < 4; i++ ) {
				vertex_pos[ i ].y = ELEVATOR_HEIGHT * MIRI_TO_METER_UNIT;
				vertex_pos[ i ] += over_size;
			}

			Model::Vertex ceiling_vertex[ 4 ] = {
				Model::Vertex( vertex_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( vertex_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ), // �E��
				Model::Vertex( vertex_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( vertex_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ), // �E��
			};
			vertex_idx = ( NORMAL_WALL + 1 ) * 6;
			_elevator_wall->setVertex( vertex_idx + 0, ceiling_vertex[ 1 ] );
			_elevator_wall->setVertex( vertex_idx + 1, ceiling_vertex[ 0 ] );
			_elevator_wall->setVertex( vertex_idx + 2, ceiling_vertex[ 2 ] );

			_elevator_wall->setVertex( vertex_idx + 3, ceiling_vertex[ 1 ] );
			_elevator_wall->setVertex( vertex_idx + 4, ceiling_vertex[ 2 ] );
			_elevator_wall->setVertex( vertex_idx + 5, ceiling_vertex[ 3 ] );

		}
	}
}

void Elevator::generateElevatorCollider( ) {
	// ������GF��y=0��6�K�w��������L�΂����߁@���� * FLOOR_NUM
	Vector pos  = Vector( 0, FLOOR_HEIGHT - ( MAX_FLOOR * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT ) / 2, ELEVATOR_WIDTH / 2 );
	Vector norm = Vector( 0, 0, -1 );
	
	// �ʏ��
	for ( int i = 0; i < WALL_COLLIDER_NUM; i++ ) {
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 * i );
		Vector pos_  = rot.multiply( pos ) + Vector( _pos.x, 0, _pos.z );
		Vector norm_ = rot.multiply( norm );
		_wall_colliders[ i ] = WallPtr( new Wall( pos_, norm_, ELEVATOR_WIDTH, FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * MAX_FLOOR ) );
	}

	// �h�A�̕�
	Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 * WALL_COLLIDER_NUM );
	Vector pos_  = rot.multiply( pos ) + Vector( _pos.x, 0, _pos.z );
	Vector norm_ = rot.multiply( norm );
	_door_collider = DoorPtr( new Door( pos_, norm_, ELEVATOR_WIDTH, FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * MAX_FLOOR ) );
}