#include "Question3FloorHint.h"
#include "QuestionManager.h"

#include "Model.h"
#include "Drawer.h"

const char* TEXTURE = "Game/Texture/Number.png";
const int NUM_SIZE = 256;
const int NUM_IMAGE_WIDTH = 2560;
const double HINT_SIZE = 500;

Question3FloorHint::Question3FloorHint( QuestionManagerConstPtr question_manager, FLOOR floor ) {
	double y = ( FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * floor * -1 ) + FLOOR_HEIGHT / 2;
	_hint = ModelPtr( new Model );
	_hint->alloc( 2 );
	_hint->setTexture( Drawer::getTask( )->getImage( TEXTURE ) );

	Vector offset = Vector( ELEVATOR_INIT_X + ELEVATOR_WIDTH / 2 + ELEVATOR_WALL_OVER_SIZE, y, ELEVATOR_INIT_Z ) * MIRI_TO_METER_UNIT;

	Vector vert_pos[ 4 ] = {
		Vector( -0.5,  0.5, 0 ) * HINT_SIZE * MIRI_TO_METER_UNIT, // ç∂è„
		Vector(  0.5,  0.5, 0 ) * HINT_SIZE * MIRI_TO_METER_UNIT, // âEè„
		Vector( -0.5, -0.5, 0 ) * HINT_SIZE * MIRI_TO_METER_UNIT, // ç∂â∫
		Vector(  0.5, -0.5, 0 ) * HINT_SIZE * MIRI_TO_METER_UNIT, // âEâ∫
	};
	// âÒì]
	Matrix rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), -PI * 0.5 );
	for ( int i = 0; i < 4; i++ ) {
		vert_pos[ i ] = rot.multiply( vert_pos[ i ] ) + offset;
	}

	int num = question_manager->getHintQuestion3( floor );
	float u1 = ( float )( NUM_SIZE * num ) / NUM_IMAGE_WIDTH;
	float u2 = u1 + ( NUM_SIZE / ( float )NUM_IMAGE_WIDTH );
	float v1 = 0.0f;
	float v2 = 1.0f;

	Model::Vertex vert[ 4 ] = {
		Model::Vertex( vert_pos[ 0 ], u1, v1, Vector( 0, 1, 0 ) ),
		Model::Vertex( vert_pos[ 1 ], u2, v1, Vector( 0, 1, 0 ) ),
		Model::Vertex( vert_pos[ 2 ], u1, v2, Vector( 0, 1, 0 ) ),
		Model::Vertex( vert_pos[ 3 ], u2, v2, Vector( 0, 1, 0 ) ),
	};

	_hint->setVertex( 0, vert[ 0 ] );
	_hint->setVertex( 1, vert[ 1 ] );
	_hint->setVertex( 2, vert[ 2 ] );

	_hint->setVertex( 3, vert[ 1 ] );
	_hint->setVertex( 4, vert[ 3 ] );
	_hint->setVertex( 5, vert[ 2 ] );
}

Question3FloorHint::~Question3FloorHint( ) {
}

void Question3FloorHint::draw( ) const {
	_hint->draw( );
}