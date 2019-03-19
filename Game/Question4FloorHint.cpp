#include "Question4FloorHint.h"
#include "QuestionManager.h"

#include "Model.h"
#include "Drawer.h"
#include "Random.h"

const char* QUESTION4_HINT_WEEK        = "Game/Texture/Question4Week.png";
const char* QUESTION4_HINT_ITERATION   = "Game/Texture/Question4Iteration.png";
const char* QUESTION4_HINT_MONTH       = "Game/Texture/MonthSpell.png";

const int MODEL_FONT_SIZE = 1000;

Question4FloorHint::Question4FloorHint( QuestionManagerConstPtr question_manager ) {
	int month = question_manager->getHintQuestion4Month( );
	int day   = question_manager->getHintQuestion4Day( );

	DrawerPtr drawer = Drawer::getTask( );
	RandomPtr random = Random::getTask( );

	// モデルの生成
	Matrix model_rot = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI * 0.5 );
	Matrix trans_rot = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI * 0.25 * random->getRand( 0, 8 ) );

	{ // month
		_month_hint_model = ModelPtr( new Model );
		_month_hint_model->alloc( 2 );
		_month_hint_model->setTexture( drawer->getImage( QUESTION4_HINT_MONTH ) );


		const int CHAR_NUM = 3;
		Vector vert_pos[ 4 ] = {
			model_rot.multiply( Vector( -MODEL_FONT_SIZE * CHAR_NUM / 2,  MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 左上
			model_rot.multiply( Vector(  MODEL_FONT_SIZE * CHAR_NUM / 2,  MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 右上
			model_rot.multiply( Vector( -MODEL_FONT_SIZE * CHAR_NUM / 2, -MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 左下
			model_rot.multiply( Vector(  MODEL_FONT_SIZE * CHAR_NUM / 2, -MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 右下
		};

		float u1 = 0.0f;
		float u2 = 1.0f;
		float v1 = ( question_manager->getHintQuestion4Month( ) - 1 ) / MONTH;
		float v2 = v1 + 1.0f / MONTH;

		Model::Vertex vert[ 4 ] = {
			Model::Vertex( vert_pos[ 0 ], u1, v1, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 1 ], u2, v1, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 2 ], u1, v2, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 3 ], u2, v2, Vector( 0, 1, 0 ) ),
		};

		_month_hint_model->setVertex( 0, vert[ 0 ] );
		_month_hint_model->setVertex( 1, vert[ 1 ] );
		_month_hint_model->setVertex( 2, vert[ 2 ] );

		_month_hint_model->setVertex( 3, vert[ 1 ] );
		_month_hint_model->setVertex( 4, vert[ 3 ] );
		_month_hint_model->setVertex( 5, vert[ 2 ] );

		int z = random->getRand( FLOOR_WIDTH / 4, FLOOR_WIDTH / 3 );
		_month_pos = trans_rot.multiply( Vector( 0, OFFSET_Y, z ) );
	}

	{ // day
		const int W_SIZE = 1500;
		_iteration_model = ModelPtr( new Model );
		_iteration_model->alloc( 2 );
		_iteration_model->setTexture( drawer->getImage( QUESTION4_HINT_ITERATION ) );

		_week_model = ModelPtr( new Model );
		_week_model->alloc( 2 );
		_week_model->setTexture( drawer->getImage( QUESTION4_HINT_WEEK ) );

		Vector vert_pos[ 4 ] = {
			model_rot.multiply( Vector( -W_SIZE / 2,  MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 左上
			model_rot.multiply( Vector(  W_SIZE / 2,  MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 右上
			model_rot.multiply( Vector( -W_SIZE / 2, -MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 左下
			model_rot.multiply( Vector(  W_SIZE / 2, -MODEL_FONT_SIZE / 2 ) ) * MIRI_TO_METER_UNIT, // 右下
		};
		
		float u1 = 0.0f;
		float u2 = 1.0f;

		int day = question_manager->getHintQuestion4Day( ) - 1;
		int col = day % 7;
		int row = day / 7;

		const float MAX_ITERATION = 5.0f;
		float iteration_v1 = row / MAX_ITERATION;
		float iteration_v2 = iteration_v1 + 1.0f / MAX_ITERATION;

		Model::Vertex iteration_vert[ 4 ] = {
			Model::Vertex( vert_pos[ 0 ], u1, iteration_v1, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 1 ], u2, iteration_v1, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 2 ], u1, iteration_v2, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 3 ], u2, iteration_v2, Vector( 0, 1, 0 ) ),
		};

		const float MAX_WEEK = 7.0f;
		float week_v1 = col / MAX_WEEK;
		float week_v2 = week_v1 + 1.0f / MAX_WEEK;

		Model::Vertex week_vert[ 4 ] = {
			Model::Vertex( vert_pos[ 0 ], u1, week_v1, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 1 ], u2, week_v1, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 2 ], u1, week_v2, Vector( 0, 1, 0 ) ),
			Model::Vertex( vert_pos[ 3 ], u2, week_v2, Vector( 0, 1, 0 ) ),
		};
		
		// iteration
		_iteration_model->setVertex( 0, iteration_vert[ 0 ] );
		_iteration_model->setVertex( 1, iteration_vert[ 1 ] );
		_iteration_model->setVertex( 2, iteration_vert[ 2 ] );

		_iteration_model->setVertex( 3, iteration_vert[ 1 ] );
		_iteration_model->setVertex( 4, iteration_vert[ 3 ] );
		_iteration_model->setVertex( 5, iteration_vert[ 2 ] );

		// week
		_week_model->setVertex( 0, week_vert[ 0 ] );
		_week_model->setVertex( 1, week_vert[ 1 ] );
		_week_model->setVertex( 2, week_vert[ 2 ] );

		_week_model->setVertex( 3, week_vert[ 1 ] );
		_week_model->setVertex( 4, week_vert[ 3 ] );
		_week_model->setVertex( 5, week_vert[ 2 ] );
		
		int x = random->getRand( FLOOR_WIDTH / 4, FLOOR_WIDTH / 3 );
		_day_pos = trans_rot.multiply( Vector( x, OFFSET_Y ) );
	}
}

Question4FloorHint::~Question4FloorHint( ) {
}

void Question4FloorHint::draw( ) const {
	_iteration_model->draw( _day_pos * MIRI_TO_METER_UNIT );
	_week_model->draw( _day_pos * MIRI_TO_METER_UNIT );
	_month_hint_model->draw( _month_pos * MIRI_TO_METER_UNIT );
}