#include "Question5FloorHint.h"
#include "QuestionManager.h"

#include "Model.h"
#include "Drawer.h"
#include "Random.h"

const char* Q5_FRAME_TEXTURE = "Game/Texture/Frame.png";
const char* Q5_NUMS_TEXTURE  = "Game/Texture/Number.png";
const char* Q5_CONSOLE_PAGE_HINT_TEXTURE = "Game/Texture/B";

Question5FloorHint::Question5FloorHint( QuestionManagerConstPtr question_manager, FLOOR floor ) {
	DrawerPtr drawer = Drawer::getTask( );
	// コンソールページ用のヒント
	//***************************************************************************
	std::string path = Q5_CONSOLE_PAGE_HINT_TEXTURE;
	path += std::to_string( floor ) + ".png";
	
	_floor_num_model = ModelPtr( new Model );
	_floor_num_model->alloc( 2 );
	_floor_num_model->setTexture( drawer->getImage( path.c_str( ) ) );

	const int WIDTH  = 16 * 80;
	const int HEIGHT =  9 * 80;
	const Vector FLOOR_NUM_POS = Vector( -FLOOR_WIDTH / 2 + 20, floor * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * -1 + FLOOR_HEIGHT / 2 );
	Vector vert_pos[ 4 ] {
		( FLOOR_NUM_POS + Vector( 0,  HEIGHT / 2, -WIDTH / 2 ) ) * MIRI_TO_METER_UNIT,
		( FLOOR_NUM_POS + Vector( 0,  HEIGHT / 2,  WIDTH / 2 ) ) * MIRI_TO_METER_UNIT,
		( FLOOR_NUM_POS + Vector( 0, -HEIGHT / 2, -WIDTH / 2 ) ) * MIRI_TO_METER_UNIT,
		( FLOOR_NUM_POS + Vector( 0, -HEIGHT / 2,  WIDTH / 2 ) ) * MIRI_TO_METER_UNIT,
	};
	Model::Vertex vert[ 4 ] = {
		Model::Vertex( vert_pos[ 0 ], 0, 0, Vector( 0, 1 ) ),
		Model::Vertex( vert_pos[ 1 ], 1, 0, Vector( 0, 1 ) ),
		Model::Vertex( vert_pos[ 2 ], 0, 1, Vector( 0, 1 ) ),
		Model::Vertex( vert_pos[ 3 ], 1, 1, Vector( 0, 1 ) ),
	};
	_floor_num_model->setVertex( 0, vert[ 0 ] );
	_floor_num_model->setVertex( 1, vert[ 1 ] );
	_floor_num_model->setVertex( 2, vert[ 2 ] );

	_floor_num_model->setVertex( 3, vert[ 1 ] );
	_floor_num_model->setVertex( 4, vert[ 3 ] );
	_floor_num_model->setVertex( 5, vert[ 2 ] );

	// 表
	//***************************************************************************
	if ( floor == FLOOR_5 ) {
		const int COL = 3;
		const int ROW = 3;
		const int SQUARE_NUM = COL * ROW;
		const int SQUARE_SIZE = FLOOR_HEIGHT / ROW;
		const Vector NORM = Vector( 0, 1, 0 );


		_frame_model = ModelPtr( new Model );
		_frame_model->alloc( SQUARE_NUM * 2 );
		_frame_model->setTexture( drawer->getImage( Q5_FRAME_TEXTURE ) );

		_nums_model  = ModelPtr( new Model );
		_nums_model->alloc( SQUARE_NUM * 2 );
		_nums_model->setTexture( drawer->getImage( Q5_NUMS_TEXTURE ) );
		std::array< unsigned char, QuestionManager::QUESTION_5_MAX_NUM > nums = question_manager->getHintQuestion5( );
	
		const Vector TABLE_POS = Vector( 0, FLOOR_5 * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * -1 + FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 - 200 );
		for ( int i = 0; i < ROW; i++ ) {
			for ( int j = 0; j < COL; j++ ) {
				double x1 = ( -1 + j ) * SQUARE_SIZE - SQUARE_SIZE * 0.5;
				double x2 = x1 + SQUARE_SIZE;
				double y1 = (  1 - i ) * SQUARE_SIZE + SQUARE_SIZE * 0.5;
				double y2 = y1 - SQUARE_SIZE;

				Vector vert_pos[ 4 ] = {
					( TABLE_POS + Vector( x1, y1 ) ) * MIRI_TO_METER_UNIT, // 左上
					( TABLE_POS + Vector( x2, y1 ) ) * MIRI_TO_METER_UNIT, // 右上
					( TABLE_POS + Vector( x1, y2 ) ) * MIRI_TO_METER_UNIT, // 左下
					( TABLE_POS + Vector( x2, y2 ) ) * MIRI_TO_METER_UNIT, // 右下
				};
			
				int vert_idx = ( i * COL + j ) * 6;

				{ // 枠
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

				{ // 数字
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

	
}

Question5FloorHint::~Question5FloorHint( ) {
}

void Question5FloorHint::draw( ) const {
	if ( _frame_model && _nums_model ) {
		_frame_model->draw( );
		_nums_model ->draw( );
	}
	_floor_num_model->draw( );
}