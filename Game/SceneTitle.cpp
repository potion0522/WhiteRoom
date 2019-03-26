#include "SceneTitle.h"
#include "Controller.h"
#include "FloorGF.h"
#include "CollideManager.h"
#include "Elevator.h"
#include "ElevatorButton.h"
#include "ElevatorAnnounce.h"
#include "SoundManager.h"

#include "Manager.h"
#include "Camera.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Image.h"
#include "Mathematics.h"

const char* TITLE_LOGO_FILEPATH      = "Title/TitleLogo.png";
const char* CLICK_TO_START_FILEPATH  = "Title/ClickToStart.png";
const char* TITLE_WHITE_OUT_FILEPATH = "White.png";

const char* START_BUTTON_TAG = "StartButton";

const Vector CAMERA_POS = Vector( FLOOR_WIDTH / 5, FLOOR_HEIGHT / 2, -FLOOR_WIDTH / 5 );
const Vector CAMERA_TAEGET = Matrix::makeTransformRotation( Vector( 0, 1 ), PI * 0.15 ).multiply( Vector( ELEVATOR_INIT_X, FLOOR_HEIGHT / 2 ) );

SceneTitle::SceneTitle( ) :
_font_count( 0 ),
_elevator_time( 0 ),
_elevator_floor( FLOOR_1 ),
_elevator_count( false ),
_white_out_start_time( 0 ),
_phase( PHASE_TITLE ) {
	CollideManagerPtr collide( new CollideManager );

	{// Elevator
		_elevator = ElevatorPtr( new Elevator( 
			Vector( ELEVATOR_INIT_X, FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT * _elevator_floor, ELEVATOR_INIT_Z ),
			collide,
			_elevator_floor
		) );
		_elevator->getAnnounceObservable( )->subscribeAnnounceArrive( [ & ]( FLOOR floor ){ 
			_elevator_floor = floor;
			_elevator_time = getNowCount( );
			_elevator_count = true;
		} );
		_elevator->getElevatorButton( )->pushButton( ( _elevator_floor == FLOOR_GF ? FLOOR_1 : FLOOR_GF ) );
	}

	// Floor
	_floor = FloorPtr( new FloorGF( collide, _elevator->getAnnounceObservable( ) ) );


	DrawerPtr drawer = Drawer::getTask( );
	{ // logo
		_logo = drawer->getImage( TITLE_LOGO_FILEPATH );
		_logo->setPos( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3 );
		_logo->setCentral( true );
	}

	{ // StartButton
		_click_to_start = drawer->getImage( CLICK_TO_START_FILEPATH );
		_click_to_start->setPos( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3 );
		_click_to_start->setCentral( true );
	}

	// whiteout
	_white_out = drawer->getImage( TITLE_WHITE_OUT_FILEPATH );
	_white_out->setBlendMode( 0 );

	// camera
	initializeCamera( );

	// mute
	SoundManager* sound = SoundManager::getInstance( );
	sound->mute( SoundManager::SE_ELEVATOR_ARRIVE );
	sound->mute( SoundManager::SE_ELEVATOR_MOVE );
}

SceneTitle::~SceneTitle( ) {
}

void SceneTitle::update( ) {
	switch ( _phase ) {
	case PHASE_TITLE:
		actOnTitle( );
		break;

	case PHASE_WHITEOUT:
		actOnWhiteOut( );
		break;
	}
}

void SceneTitle::draw( ) const {
	_floor->draw( );
	_elevator->draw( );
	_click_to_start->draw( );
	_logo->draw( );
	if ( _phase == PHASE_WHITEOUT ) {
		_white_out->draw( );
	}

	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );
}

void SceneTitle::actOnTitle( ) {
	// クリック判定
	updateMouse( );

	// ボタン状態の更新
	updateStartButton( );

	// エレベーターの更新
	updateElevator( );
}

void SceneTitle::actOnWhiteOut( ) {
	// 遷移
	int now = getNowCount( );
	if ( now - _white_out_start_time > WHITE_OUT_TIME ) {
		Controller::getTask( )->setNextScene( Controller::SCENE_GAME );
	} else {
		// alpha計算
		double ratio = ( now - _white_out_start_time ) / ( double )WHITE_OUT_TIME;
		int alpha = ( int )( 255 * ratio );
		_white_out->setBlendMode( alpha );
	}
}

void SceneTitle::initializeCamera( ) {
	CameraPtr camera = Camera::getTask( );
	camera->setCameraUp( Vector( 0, 1 ) );
	camera->setCamera( 
		CAMERA_POS * MIRI_TO_METER_UNIT, 
		CAMERA_TAEGET * MIRI_TO_METER_UNIT 
	);
}

void SceneTitle::updateMouse( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->isClickUpLeft( ) ) {
		_phase = PHASE_WHITEOUT;
		_white_out_start_time = getNowCount( );
	}
}

void SceneTitle::updateStartButton( ) {
	// 点滅処理
	const int MAX_ALPHA = 255;
	_font_count = ( _font_count + 1 ) % ( int )( FONT_FLASHING_RATIO + 1 );

	// 0～1の波
	double flashing = ( sin( ( PI * 2 ) / FONT_FLASHING_RATIO * _font_count ) + 1 ) / 2 * FONT_FLASHING_ALPHA;
	int alpha = MAX_ALPHA - ( int )flashing;

	_click_to_start->setBlendMode( alpha );
}

void SceneTitle::updateElevator( ) {
	_elevator->update( );

	// 移動処理
	if ( _elevator_count ) {
		int now = getNowCount( );
		if ( now - _elevator_time > ELEVATOR_MOVE_TIME ) {
			ElevatorButtonPtr button = _elevator->getElevatorButton( );
			FLOOR order_floor = ( _elevator_floor == FLOOR_GF ? FLOOR_1 : FLOOR_GF );
			button->pushButton( order_floor );
			_elevator_count = false;
		}
	}
}

int SceneTitle::getNowCount( ) const {
	return Manager::getInstance( )->getNowCount( );
}