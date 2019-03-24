#include "Question5FloorHint.h"
#include "QuestionManager.h"

#include "Model.h"
#include "Drawer.h"
#include "Random.h"

const char* Q5_FRAME_TEXTURE = "Game/Texture/Frame.png";
const char* Q5_NUMS_TEXTURE  = "Game/Texture/Number.png";

Question5FloorHint::Question5FloorHint( QuestionManagerConstPtr question_manager ) {
	const int COL = 3;
	const int ROW = 3;
	const int SQUARE_NUM = COL * ROW;
	const int SQUARE_SIZE = FLOOR_HEIGHT / ROW;
	const Vector NORM = Vector( 0, 1, 0 );

	DrawerPtr drawer = Drawer::getTask( );

	_frame_model = ModelPtr( new Model );
	_frame_model->alloc( SQUARE_NUM * 2 );
	_frame_model->setTexture( drawer->getImage( Q5_FRAME_TEXTURE ) );

	_nums_model  = ModelPtr( new Model );
	_nums_model->alloc( SQUARE_NUM * 2 );
	_nums_model->setTexture( drawer->getImage( Q5_NUMS_TEXTURE ) );
	std::array< unsigned char, QuestionManager::QUESTION_5_MAX_NUM > nums = question_manager->getHintQuestion5( );
	
	for ( int i = 0; i < ROW; i++ ) {
		for ( int j = 0; j < COL; j++ ) {
			double x1 = ( -1 + j ) * SQUARE_SIZE - SQUARE_SIZE * 0.5;
			double x2 = x1 + SQUARE_SIZE;
			double y1 = (  1 - i ) * SQUARE_SIZE + SQUARE_SIZE * 0.5;
			double y2 = y1 - SQUARE_SIZE;

			Vector vert_pos[ 4 ] = {
				Vector( x1, y1 ) * MIRI_TO_METER_UNIT, // ¶ã
				Vector( x2, y1 ) * MIRI_TO_METER_UNIT, // ‰Eã
				Vector( x1, y2 ) * MIRI_TO_METER_UNIT, // ¶‰º
				Vector( x2, y2 ) * MIRI_TO_METER_UNIT, // ‰E‰º
			};
			
			int vert_idx = ( i * COL + j ) * 6;

			{ // ˜g
				float u1 = 0.0f;
				float u2 = 1.0f;
				float v1 = 0.0f;
				float v2 = 1.0f;

				Model::Vertex vert[ 4 ] = {
					Model::Vertex( vert_pos[ 0 ], u1, v1, NORM ),
					Model::Vertex( vert_pos[ 1 ], u2, v1, NORM ),
					Model::Vertex( vert_pos[ 2 ], u1, v2, NORM ),
					Model::Vertex( vert_pos[ 3 ], u2, v2, NORM ),
				};

				_frame_model->setVertex( vert_idx + 0, vert[ 0 ] );
				_frame_model->setVertex( vert_idx + 1, vert[ 1 ] );
				_frame_model->setVertex( vert_idx + 2, vert[ 2 ] );

				_frame_model->setVertex( vert_idx + 3, vert[ 1 ] );
				_frame_model->setVertex( vert_idx + 4, vert[ 3 ] );
				_frame_model->setVertex( vert_idx + 5, vert[ 2 ] );
			}

			{ // ”Žš
				int idx = j + i * COL;
				const int TEXTURE_MAX_NUM = 10;
				float u1 = nums[ idx ] / ( float )TEXTURE_MAX_NUM;
				float u2 = u1 + 1.0f / TEXTURE_MAX_NUM;
				float v1 = 0.0f;
				float v2 = 1.0f;

				Model::Vertex vert[ 4 ] = {
					Model::Vertex( vert_pos[ 0 ], u1, v1, NORM ),
					Model::Vertex( vert_pos[ 1 ], u2, v1, NORM ),
					Model::Vertex( vert_pos[ 2 ], u1, v2, NORM ),
					Model::Vertex( vert_pos[ 3 ], u2, v2, NORM ),
				};

				_nums_model->setVertex( vert_idx + 0, vert[ 0 ] );
				_nums_model->setVertex( vert_idx + 1, vert[ 1 ] );
				_nums_model->setVertex( vert_idx + 2, vert[ 2 ] );

				_nums_model->setVertex( vert_idx + 3, vert[ 1 ] );
				_nums_model->setVertex( vert_idx + 4, vert[ 3 ] );
				_nums_model->setVertex( vert_idx + 5, vert[ 2 ] );
			}
		}
	}
}

Question5FloorHint::~Question5FloorHint( ) {
}

void Question5FloorHint::draw( ) const {
	const Vector POS = Vector( 0, FLOOR_5 * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * -1 + FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 - 200 );
	_frame_model->draw( POS * MIRI_TO_METER_UNIT );
	_nums_model ->draw( POS * MIRI_TO_METER_UNIT );
}