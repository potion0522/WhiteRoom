#include "Floor.h"
#include "define.h"
#include "Wall.h"
#include "CollideManager.h"
#include "ElevatorAnnounceObservable.h"

#include "Model.h"
#include "Mathematics.h"
#include "Drawer.h"
#include "Manager.h"

const char* ROOM_TEXTURE = "Game/Texture/WallTexture.png";

Floor::Floor( CollideManagerPtr collide_manager, ElevatorAnnounceObservablePtr observable, FLOOR floor ) :
_floor( floor ) {
	// y���W�v�Z
	_y = ( int )_floor * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * -1;

	// ����(�ǁE��)�̐���
	generateFloor( );
	generateFloorCollider( );

	// �����蔻����}�l�[�W���[�ɓo�^����
	setColliderToCollideManager( collide_manager );

	// �G���x�[�^�[�̒ʒm
	observable->subscribeAnnounceArrive( 
		[ & ]( FLOOR elevator_floor ) { 
		if ( elevator_floor == _floor ) {	
			_elevator_side_wall->setEnabled( false );
		} else {
			_elevator_side_wall->setEnabled( true );
		}
	} );

	// �G���x�[�^�[�̏����n�_�Ɠ����Ȃ��A�N�e�B�u�ɂ���
	if ( _floor == ELEVATOR_INIT_FLOOR ) {
		_elevator_side_wall->setEnabled( false );
	}
}

Floor::~Floor( ) {
}

void Floor::update( ) {
}

void Floor::draw( ) const {
	_floor_model->draw( );
}

double Floor::getY( ) const {
	return _y;
}

void Floor::generateFloor( ) {
	_floor_model = ModelPtr( new Model );

	const int NORMAL_WALL   = 3;
	const int ELEVATOR_WALL = 2;
	const int FLOOR_PLANE   = 2;
	_floor_model->alloc( ( NORMAL_WALL + ELEVATOR_WALL + FLOOR_PLANE ) * 2 );

	_floor_model->setTexture( Drawer::getTask( )->getImage( ROOM_TEXTURE ) );

	{ // ��3��
		Vector vertex_pos[ 4 ] = {
			Vector( -FLOOR_WIDTH / 2, _y + FLOOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(  FLOOR_WIDTH / 2, _y + FLOOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -FLOOR_WIDTH / 2, _y +            0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector(  FLOOR_WIDTH / 2, _y +            0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
		};						 

		for ( int i = 0; i < NORMAL_WALL; i++ ) {
			// 90�x�̉�]�s��
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * i );

			Model::Vertex vertex[ 4 ] = {
				Model::Vertex( rot.multiply( vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
				Model::Vertex( rot.multiply( vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
			};

			int vertex_idx = i * 6;
			_floor_model->setVertex( vertex_idx + 0, vertex[ 0 ] );
			_floor_model->setVertex( vertex_idx + 1, vertex[ 1 ] );
			_floor_model->setVertex( vertex_idx + 2, vertex[ 2 ] );

			_floor_model->setVertex( vertex_idx + 3, vertex[ 1 ] );
			_floor_model->setVertex( vertex_idx + 4, vertex[ 3 ] );
			_floor_model->setVertex( vertex_idx + 5, vertex[ 2 ] );
		}
	}



	{ // �G���x�[�^�[�̂����
		const double WALL_WIDTH = ( FLOOR_WIDTH / 2 - ELEVATOR_WIDTH / 2 );

		// 270�x�̉�]�s��(�ǂ�4���Ȃ̂�)
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * NORMAL_WALL );

		// ����
		Vector left_side_vertex_pos[ 4 ] = {
			Vector( -FLOOR_WIDTH / 2             , _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector( -FLOOR_WIDTH / 2 + WALL_WIDTH, _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			Vector( -FLOOR_WIDTH / 2             , _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector( -FLOOR_WIDTH / 2 + WALL_WIDTH, _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
		};
		Model::Vertex left_side_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};

		int vertex_idx = NORMAL_WALL * 6;
		_floor_model->setVertex( vertex_idx + 0, left_side_vertex[ 0 ] );
		_floor_model->setVertex( vertex_idx + 1, left_side_vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 2, left_side_vertex[ 2 ] );

		_floor_model->setVertex( vertex_idx + 3, left_side_vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 4, left_side_vertex[ 3 ] );
		_floor_model->setVertex( vertex_idx + 5, left_side_vertex[ 2 ] );


		// �E��
		Vector right_side_vertex_pos[ 4 ] = {
			Vector( FLOOR_WIDTH / 2 - WALL_WIDTH, _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector( FLOOR_WIDTH / 2             , _y + ELEVATOR_HEIGHT, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
			Vector( FLOOR_WIDTH / 2 - WALL_WIDTH, _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // ����
			Vector( FLOOR_WIDTH / 2             , _y +               0, FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, // �E��
		};
		Model::Vertex right_side_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};

		vertex_idx = ( NORMAL_WALL + 1 ) * 6;
		_floor_model->setVertex( vertex_idx + 0, right_side_vertex[ 0 ] );
		_floor_model->setVertex( vertex_idx + 1, right_side_vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 2, right_side_vertex[ 2 ] );

		_floor_model->setVertex( vertex_idx + 3, right_side_vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 4, right_side_vertex[ 3 ] );
		_floor_model->setVertex( vertex_idx + 5, right_side_vertex[ 2 ] );
	}




	{ // �� �V��

		Model::Vertex vertex[ 4 ] = {
			Model::Vertex( Vector( -FLOOR_WIDTH / 2, _y,  FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( Vector(  FLOOR_WIDTH / 2, _y,  FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( Vector( -FLOOR_WIDTH / 2, _y, -FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( Vector(  FLOOR_WIDTH / 2, _y, -FLOOR_WIDTH / 2 ) * MIRI_TO_METER_UNIT, 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};

		// ��
		int vertex_idx = ( NORMAL_WALL + ELEVATOR_WALL ) * 6;
		_floor_model->setVertex( vertex_idx + 0, vertex[ 0 ] );
		_floor_model->setVertex( vertex_idx + 1, vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 2, vertex[ 2 ] );

		_floor_model->setVertex( vertex_idx + 3, vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 4, vertex[ 3 ] );
		_floor_model->setVertex( vertex_idx + 5, vertex[ 2 ] );

		// �V��
		for ( int i = 0; i < 4; i++ ) {
			vertex[ i ].pos += Vector( 0, FLOOR_HEIGHT, 0 ) * MIRI_TO_METER_UNIT;
		}

		vertex_idx = ( NORMAL_WALL + ELEVATOR_WALL + 1 ) * 6;
		_floor_model->setVertex( vertex_idx + 0, vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 1, vertex[ 0 ] );
		_floor_model->setVertex( vertex_idx + 2, vertex[ 2 ] );
															
		_floor_model->setVertex( vertex_idx + 3, vertex[ 1 ] );
		_floor_model->setVertex( vertex_idx + 4, vertex[ 2 ] );
		_floor_model->setVertex( vertex_idx + 5, vertex[ 3 ] );

	}
}

void Floor::generateFloorCollider( ) {
	const double OVER_SIZE = 500; // ������Ƃ����傫�߂ɔ�������

	{ // �ʏ�ǂ̓����蔻��
		Vector norm = Vector( 0, 0, -1 );
		Vector pos  = Vector( 0, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 );

		for ( int i = 0; i < NORMAL_WALL_NUM; i++ ) {
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * i );
			Vector pos_  = rot.multiply( pos ) + Vector( 0, _y, 0 );
			Vector norm_ = rot.multiply( norm );
			_wall_colliders[ i ] = WallPtr( new Wall( pos_, norm_, FLOOR_WIDTH + OVER_SIZE, FLOOR_HEIGHT ) );
		}
	}
	
	{ // �G���x�[�^�[�̂���� + ���̗��[�̕�
		const double SIDE_WALL_WIDTH     = ( FLOOR_WIDTH - ELEVATOR_WIDTH ) / 2;
		const double ELEVATOR_WALL_WIDTH = ELEVATOR_WIDTH;

		Vector norm = Vector( 0, 0, -1 );
		Vector pos[ ELEVATOR_SIDE_WALL_NUM ] = {
			Vector( -FLOOR_WIDTH / 2, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 ) + Vector( SIDE_WALL_WIDTH / 2, 0, 0 ),
			Vector(  FLOOR_WIDTH / 2, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 ) - Vector( SIDE_WALL_WIDTH / 2, 0, 0 ),
		};

		// 270�x��]
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.5 * 3 );
		for ( int i = 0; i < ELEVATOR_SIDE_WALL_NUM; i++ ) {
			pos[ i ] = rot.multiply( pos[ i ] ) + Vector( 0, _y, 0 );
		}
		norm = rot.multiply( norm );

		// ��]�������W�œ����蔻��𐶐�
		_wall_colliders[ NORMAL_WALL_NUM + 0 ] = WallPtr( new Wall( pos[ 0 ], norm, SIDE_WALL_WIDTH + OVER_SIZE, FLOOR_HEIGHT ) );
		_wall_colliders[ NORMAL_WALL_NUM + 1 ] = WallPtr( new Wall( pos[ 1 ], norm, SIDE_WALL_WIDTH + OVER_SIZE, FLOOR_HEIGHT ) );



		// �G���x�[�^�[�̂����
		_elevator_side_wall = WallPtr( new Wall( rot.multiply( Vector( 0, FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 ) + Vector( 0, _y, 0 ) ), norm, ELEVATOR_WALL_WIDTH + OVER_SIZE, FLOOR_HEIGHT, OBJECT_TAG_ELEVATOR_SIDE_WALL ) );
	}

}

void Floor::setColliderToCollideManager( CollideManagerPtr collide_manager ) {
	// ��
	for ( int i = 0; i < NORMAL_WALL_NUM + ELEVATOR_SIDE_WALL_NUM; i++ ) {
		collide_manager->addStaticCollider( _wall_colliders[ i ] );
	}
	collide_manager->addStaticCollider( _elevator_side_wall );
}