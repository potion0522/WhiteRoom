#include "Question1FloorHint.h"
#include "QuestionManager.h"

#include "Drawer.h"
#include "Model.h"
#include "Random.h"

#include <array>


const char* TEXTURE_FILE = "Game/Texture/Q1HintTexture.png";

Question1FloorHint::Question1FloorHint( QuestionManagerConstPtr question_manager ) {
	DrawerPtr drawer = Drawer::getTask( );
	_hint = ModelPtr( new Model );

	const int COL = 3;
	const int ROW = 3;
	const int SQUARE_NUM = COL * ROW;
	_hint->alloc( SQUARE_NUM * 6 );
	_hint->setTexture( drawer->getImage( TEXTURE_FILE ) );

	// 全体のサイズ
	const double MODEL_SIZE  = FLOOR_HEIGHT;
	const double SQUARE_SIZE = MODEL_SIZE / COL;

	// 左上基準

	std::array< unsigned char, 3 > answer = question_manager->getHintQuestion1( );
	Vector norm = Vector( 0, 1, 0 );
	Vector base_pos = Vector( -MODEL_SIZE / 2, MODEL_SIZE / 2, 0 );

	// ランダムで回転させる
	RandomPtr random = Random::getTask( );
	Matrix rot = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI * 0.5 * random->getRand( 1, 3 ) );

	for ( int i = 0; i < ROW; i++ ) {
		for ( int j = 0; j < COL; j++ ) {
			double x1 = ( -1 + j ) * SQUARE_SIZE - SQUARE_SIZE * 0.5;
			double x2 = x1 + SQUARE_SIZE;
			double y1 = (  1 - i ) * SQUARE_SIZE + SQUARE_SIZE * 0.5;
			double y2 = y1 - SQUARE_SIZE;

			Vector vert_pos[ 4 ] = {
				rot.multiply( Vector( x1, y1 ) ) * MIRI_TO_METER_UNIT, // 左上
				rot.multiply( Vector( x2, y1 ) ) * MIRI_TO_METER_UNIT, // 右上
				rot.multiply( Vector( x1, y2 ) ) * MIRI_TO_METER_UNIT, // 左下
				rot.multiply( Vector( x2, y2 ) ) * MIRI_TO_METER_UNIT, // 右下
			};

			// 答えの部分は黒にする
			int square_idx = i * COL + j;
			float u = 0.0f;
			if ( square_idx == answer[ 0 ] || square_idx == answer[ 1 ] || square_idx == answer[ 2 ] ) {
				u = 0.5f;
			}

			Model::Vertex vert[ 4 ] = {
				Model::Vertex( vert_pos[ 0 ], 0.0f + u, 0.0f, norm ),
				Model::Vertex( vert_pos[ 1 ], 0.5f + u, 0.0f, norm ),
				Model::Vertex( vert_pos[ 2 ], 0.0f + u, 1.0f, norm ),
				Model::Vertex( vert_pos[ 3 ], 0.5f + u, 1.0f, norm ),
			};

			int idx = ( i * COL + j ) * 6;
			_hint->setVertex( idx + 0, vert[ 0 ] );
			_hint->setVertex( idx + 1, vert[ 1 ] );
			_hint->setVertex( idx + 2, vert[ 2 ] );
										  
			_hint->setVertex( idx + 3, vert[ 1 ] );
			_hint->setVertex( idx + 4, vert[ 3 ] );
			_hint->setVertex( idx + 5, vert[ 2 ] );
		}
	}

}

Question1FloorHint::~Question1FloorHint( ) {
}

void Question1FloorHint::draw( ) const {
	const Vector POS = Vector( 0, FLOOR_2 * FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * -1 + FLOOR_HEIGHT / 2, FLOOR_WIDTH / 2 - 200 );
	_hint->draw( POS * MIRI_TO_METER_UNIT );
}
