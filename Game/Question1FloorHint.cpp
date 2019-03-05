#include "Question1FloorHint.h"
#include "QuestionManager.h"
#include "define.h"

#include "Drawer.h"
#include "Model.h"

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

	const int SQUARE_WIDTH = FLOOR_HEIGHT / 3;

	// 左上基準
	Vector ver_pos[ 4 ] = {
		Vector(            0,             0, 0 ) + Vector( 0, -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * FLOOR_1 + FLOOR_HEIGHT, FLOOR_WIDTH / 2 - 100 ), // 左上
		Vector( SQUARE_WIDTH,             0, 0 ) + Vector( 0, -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * FLOOR_1 + FLOOR_HEIGHT, FLOOR_WIDTH / 2 - 100 ), // 右上
		Vector(            0, -SQUARE_WIDTH, 0 ) + Vector( 0, -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * FLOOR_1 + FLOOR_HEIGHT, FLOOR_WIDTH / 2 - 100 ), // 左下
		Vector( SQUARE_WIDTH, -SQUARE_WIDTH, 0 ) + Vector( 0, -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * FLOOR_1 + FLOOR_HEIGHT, FLOOR_WIDTH / 2 - 100 ), // 右下
	};

	std::array< unsigned char, 3 > answer = question_manager->getHintQuestion1( );

	for ( int i = 0; i < ROW; i++ ) {
		for ( int j = 0; j < COL; j++ ) {
			Vector norm = Vector( 0, 1, 0 );
			float u = 0.0;
			int square_idx = i * COL + j;

			// 答えの部分は黒にする
			if ( square_idx == answer[ 0 ] || square_idx == answer[ 1 ] || square_idx == answer[ 2 ] ) {
				u = 0.5;
			}

			// マスをずらす
			Vector offset;
			offset.x = j * SQUARE_WIDTH *  1;
			offset.y = i * SQUARE_WIDTH * -1;

			Model::Vertex ver[ 4 ] = {
				Model::Vertex( ( ver_pos[ 0 ] + offset ) * MIRI_TO_METER_UNIT, 0.0f + u, 0.0f, norm ),
				Model::Vertex( ( ver_pos[ 1 ] + offset ) * MIRI_TO_METER_UNIT, 0.5f + u, 0.0f, norm ),
				Model::Vertex( ( ver_pos[ 2 ] + offset ) * MIRI_TO_METER_UNIT, 0.0f + u, 1.0f, norm ),
				Model::Vertex( ( ver_pos[ 3 ] + offset ) * MIRI_TO_METER_UNIT, 0.5f + u, 1.0f, norm ),
			};

			int idx = ( i * COL + j ) * 6;
			_hint->setVertex( idx + 0, ver[ 0 ] );
			_hint->setVertex( idx + 1, ver[ 1 ] );
			_hint->setVertex( idx + 2, ver[ 2 ] );

			_hint->setVertex( idx + 3, ver[ 1 ] );
			_hint->setVertex( idx + 4, ver[ 3 ] );
			_hint->setVertex( idx + 5, ver[ 2 ] );
		}
	}
}

Question1FloorHint::~Question1FloorHint( ) {
}

void Question1FloorHint::drawQuestion1Hint( ) const {
	_hint->draw( );
}
