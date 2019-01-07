#include "Floor.h"
#include "define.h"

#include "Model.h"
#include "Mathematics.h"
#include "Drawer.h"

const char* ROOM_TEXTURE = "Game/Texture/FloorTexture.png";

Floor::Floor( double y ) :
_y( y ) {
	// ����(�ǁE��)�̐���
	generateRoom( );
}

Floor::~Floor( ) {
}

void Floor::draw( ) const {
	_floor->draw( );
}

double Floor::getY( ) const {
	return _y;
}

void Floor::generateRoom( ) {
	_floor = ModelPtr( new Model );

	const int NORMAL_WALL   = 3;
	const int ELEVATOR_WALL = 2;
	const int FLOOR_NUM     = 1;
	_floor->alloc( ( NORMAL_WALL + ELEVATOR_WALL + FLOOR_NUM ) * 2 );

	_floor->setTexture( Drawer::getTask( )->getImage( ROOM_TEXTURE ) );


	int vertex_idx = 0;
	{ // ��3��
		Vector vertex_pos[ 4 ] = {
			Vector( -FLOOR_WIDTH, _y + FLOOR_HEIGHT, FLOOR_WIDTH ), // ����
			Vector(  FLOOR_WIDTH, _y + FLOOR_HEIGHT, FLOOR_WIDTH ), // �E��
			Vector( -FLOOR_WIDTH, _y +           0, FLOOR_WIDTH ), // ����
			Vector(  FLOOR_WIDTH, _y +           0, FLOOR_WIDTH ), // �E��
		};

		for ( int i = 0; i < NORMAL_WALL; i++ ) {
			// 90�x�̉�]�s��
			Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.25 * i );

			Model::Vertex vertex[ 4 ] = {
				Model::Vertex( rot.multiply( vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
				Model::Vertex( rot.multiply( vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
				Model::Vertex( rot.multiply( vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
			};


			_floor->setVertex( vertex_idx + 0, vertex[ 0 ] );
			_floor->setVertex( vertex_idx + 1, vertex[ 1 ] );
			_floor->setVertex( vertex_idx + 2, vertex[ 2 ] );

			_floor->setVertex( vertex_idx + 3, vertex[ 1 ] );
			_floor->setVertex( vertex_idx + 4, vertex[ 3 ] );
			_floor->setVertex( vertex_idx + 5, vertex[ 2 ] );

			vertex_idx += 6;
		}
	}



	{ // �G���x�[�^�[�̂����
		const double WALL_WIDTH = ( FLOOR_WIDTH - ELEVATOR_WIDTH );

		// 270�x�̉�]�s��(�ǂ�4���Ȃ̂�)
		Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.25 * NORMAL_WALL );

		// ����
		Vector left_side_vertex_pos[ 4 ] = {
			Vector( -FLOOR_WIDTH             , _y + ELEVATOR_HEIGHT, FLOOR_WIDTH ), // ����
			Vector( -FLOOR_WIDTH + WALL_WIDTH, _y + ELEVATOR_HEIGHT, FLOOR_WIDTH ), // �E��
			Vector( -FLOOR_WIDTH             , _y +               0, FLOOR_WIDTH ), // ����
			Vector( -FLOOR_WIDTH + WALL_WIDTH, _y +               0, FLOOR_WIDTH ), // �E��
		};
		Model::Vertex left_side_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( left_side_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		_floor->setVertex( vertex_idx + 0, left_side_vertex[ 0 ] );
		_floor->setVertex( vertex_idx + 1, left_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 2, left_side_vertex[ 2 ] );

		_floor->setVertex( vertex_idx + 3, left_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 4, left_side_vertex[ 3 ] );
		_floor->setVertex( vertex_idx + 5, left_side_vertex[ 2 ] );

		vertex_idx += 6;

		// �E��
		Vector right_side_vertex_pos[ 4 ] = {
			Vector( FLOOR_WIDTH - WALL_WIDTH, _y + ELEVATOR_HEIGHT, FLOOR_WIDTH ), // ����
			Vector( FLOOR_WIDTH             , _y + ELEVATOR_HEIGHT, FLOOR_WIDTH ), // �E��
			Vector( FLOOR_WIDTH - WALL_WIDTH, _y +               0, FLOOR_WIDTH ), // ����
			Vector( FLOOR_WIDTH             , _y +               0, FLOOR_WIDTH ), // �E��
		};
		Model::Vertex right_side_vertex[ 4 ] = {
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 0 ] ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 1 ] ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 2 ] ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( rot.multiply( right_side_vertex_pos[ 3 ] ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};
		_floor->setVertex( vertex_idx + 0, right_side_vertex[ 0 ] );
		_floor->setVertex( vertex_idx + 1, right_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 2, right_side_vertex[ 2 ] );

		_floor->setVertex( vertex_idx + 3, right_side_vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 4, right_side_vertex[ 3 ] );
		_floor->setVertex( vertex_idx + 5, right_side_vertex[ 2 ] );

		vertex_idx += 6;
	}




	{ // ��
		Model::Vertex vertex[ 4 ] = {
			Model::Vertex( Vector( -FLOOR_WIDTH, _y,  FLOOR_WIDTH ), 0, 0, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( Vector(  FLOOR_WIDTH, _y,  FLOOR_WIDTH ), 1, 0, Vector( 0, 1, 0 ) ), // �E��
			Model::Vertex( Vector( -FLOOR_WIDTH, _y, -FLOOR_WIDTH ), 0, 1, Vector( 0, 1, 0 ) ), // ����
			Model::Vertex( Vector(  FLOOR_WIDTH, _y, -FLOOR_WIDTH ), 1, 1, Vector( 0, 1, 0 ) ), // �E��
		};

		_floor->setVertex( vertex_idx + 0, vertex[ 0 ] );
		_floor->setVertex( vertex_idx + 1, vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 2, vertex[ 2 ] );

		_floor->setVertex( vertex_idx + 3, vertex[ 1 ] );
		_floor->setVertex( vertex_idx + 4, vertex[ 3 ] );
		_floor->setVertex( vertex_idx + 5, vertex[ 2 ] );

		vertex_idx += 6;
	}
}