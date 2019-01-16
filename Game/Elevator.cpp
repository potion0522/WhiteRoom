#include "Elevator.h"
#include "define.h"

#include "Drawer.h"
#include "Model.h"

const char* ELEVATOR_TEXTURE = "Game/Texture/ElevatorTexture.png";

Elevator::Elevator( const Vector& init_pos ) :
_pos( init_pos ) {
	// ���f���̍쐬
	generateElevator( );
}

Elevator::~Elevator( ) {
}

void Elevator::draw( ) const {
	_model->draw( _pos );
}

void Elevator::generateElevator( ) {
	_model = ModelPtr( new Model );

	const int NORMAL_WALL = 3;
	const int DOOR        = 2;
	const int OTHER_WALL  = 2; // �V��Ə�
	_model->alloc( ( NORMAL_WALL + DOOR + OTHER_WALL ) * 2 );

	_model->setTexture( Drawer::getTask( )->getImage( ELEVATOR_TEXTURE ) );

	{ // �ʏ��
		Vector vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ), // ����
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ), // �E��
			Vector( -ELEVATOR_WIDTH,               0, ELEVATOR_WIDTH ), // ����
			Vector(  ELEVATOR_WIDTH,               0, ELEVATOR_WIDTH ), // �E��
		};

		for ( int i = 0; i < NORMAL_WALL; i++ ) {
			// 90�x�̉�]�s��
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.25 * i );

			Model::Vertex vertex[ 4 ] = {
				Model::Vertex( rot.multiply( vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
				Model::Vertex( rot.multiply( vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
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

	{ // �J����h�A
		const double DOOR_WIDTH = ELEVATOR_WIDTH / 2;
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.25 * NORMAL_WALL );

		// ����
		Vector left_door_vertex_pos[ 4 ] = {
			Vector( -DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ), // ����
			Vector(           0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ), // �E��
			Vector( -DOOR_WIDTH,               0, ELEVATOR_WIDTH ), // ����
			Vector(           0,               0, ELEVATOR_WIDTH ), // �E��
		};
		Model::Vertex left_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		int vertex_idx = NORMAL_WALL * 6;
		_model->setVertex( vertex_idx + 0, left_door_vertex[ 0 ] );
		_model->setVertex( vertex_idx + 1, left_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 2, left_door_vertex[ 2 ] );

		_model->setVertex( vertex_idx + 3, left_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 4, left_door_vertex[ 3 ] );
		_model->setVertex( vertex_idx + 5, left_door_vertex[ 2 ] );


		// �E��
		Vector right_door_vertex_pos[ 4 ] = {
			Vector(          0, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ), // ����
			Vector( DOOR_WIDTH, ELEVATOR_HEIGHT, ELEVATOR_WIDTH ), // �E��
			Vector(          0,               0, ELEVATOR_WIDTH ), // ����
			Vector( DOOR_WIDTH,               0, ELEVATOR_WIDTH ), // �E��
		};
		Model::Vertex right_door_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_door_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		vertex_idx = ( NORMAL_WALL + 1 ) * 6;
		_model->setVertex( vertex_idx + 0, right_door_vertex[ 0 ] );
		_model->setVertex( vertex_idx + 1, right_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 2, right_door_vertex[ 2 ] );

		_model->setVertex( vertex_idx + 3, right_door_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 4, right_door_vertex[ 3 ] );
		_model->setVertex( vertex_idx + 5, right_door_vertex[ 2 ] );
	}


	{ // ���ƓV��

		// ��
		Vector floor_vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, 0,  ELEVATOR_WIDTH ), // ����
			Vector(  ELEVATOR_WIDTH, 0,  ELEVATOR_WIDTH ), // �E��
			Vector( -ELEVATOR_WIDTH, 0, -ELEVATOR_WIDTH ), // ����
			Vector(  ELEVATOR_WIDTH, 0, -ELEVATOR_WIDTH ), // �E��
		};
		Model::Vertex floor_vertex[ 4 ] = {
			Model::Vertex( floor_vertex_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( floor_vertex_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( floor_vertex_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( floor_vertex_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		int vertex_idx = ( NORMAL_WALL + DOOR ) * 6;
		_model->setVertex( vertex_idx + 0, floor_vertex[ 0 ] );
		_model->setVertex( vertex_idx + 1, floor_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 2, floor_vertex[ 2 ] );

		_model->setVertex( vertex_idx + 3, floor_vertex[ 1 ] );
		_model->setVertex( vertex_idx + 4, floor_vertex[ 3 ] );
		_model->setVertex( vertex_idx + 5, floor_vertex[ 2 ] );
		

		// �V��
		Vector ceiling_vertex_pos[ 4 ] = {
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT,  ELEVATOR_WIDTH ), // ����
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT,  ELEVATOR_WIDTH ), // �E��
			Vector( -ELEVATOR_WIDTH, ELEVATOR_HEIGHT, -ELEVATOR_WIDTH ), // ����
			Vector(  ELEVATOR_WIDTH, ELEVATOR_HEIGHT, -ELEVATOR_WIDTH ), // �E��
		};
		Model::Vertex ceiling_vertex[ 4 ] = {
			Model::Vertex( ceiling_vertex_pos[ 0 ], 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( ceiling_vertex_pos[ 1 ], 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( ceiling_vertex_pos[ 2 ], 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( ceiling_vertex_pos[ 3 ], 1, 1, Vector( 0, 1, 0 ) ), // �E��
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
