#include "Player.h"
#include "define.h"
#include "ElevatorBox.h"
#include "SquareCollider.h"
#include "ConsoleActiveObservable.h"
#include "SoundManager.h"

#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Sound.h"

// ラジアン = 度 * 円周率 / 180
const double MAX_H_RADIAN = 45 * PI / 180; // 横
const double MAX_V_RADIAN = 15 * PI / 180; // 縦

const double PLAYER_MOVE_SPEED = 150.0;
const double PLAYER_HEIGHT = 1500.0;
const double PLAYER_COLLIDER_RADIUS = 500.0;
const double WALK_SOUND_DISTANCE = 1500.0; // この距離歩いたら音を鳴らす

PTR( SphereCollider );
PTR( SquareCollider );

Player::Player( ElevatorBoxPtr elevator_box, ConsoleActiveObservablePtr console_observable ) :
SphereCollider( _head_pos, PLAYER_COLLIDER_RADIUS, OBJECT_TAG_PLAYER ),
_console_active( false ),
_ground_pos( 0, PLAYER_INIT_FLOOR * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT, 0 ),
_head_pos( 0, _ground_pos.y + PLAYER_HEIGHT, 0 ),
_past_sound_pos( _ground_pos ),
_dir( 0, 0, 1 ),
_floor( PLAYER_INIT_FLOOR ),
_elevator_box( elevator_box ),
_update_type( UPDATE_TYPE_ALL ) {
	// コンソールのアクティブ通知を受け取る
	console_observable->subscribeOnActive( [ & ]( bool active ) { 
		_console_active = active;
		// コンソールを解除したらマウスを真ん中に合わせる
		if ( !_console_active ) {
			Mouse::getTask( )->setMousePoint( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );
		}
	} );


	// カメラ初期設定
	CameraPtr camera = Camera::getTask( );
	camera->setCamera( _head_pos * MIRI_TO_METER_UNIT, ( _head_pos + _dir ) * MIRI_TO_METER_UNIT );
	camera->setCameraUp( Vector( 0, 1, 0 ) );
	camera->setNearFar( 100.0f * ( float )MIRI_TO_METER_UNIT, ( float )( FLOOR_WIDTH * 2 * MIRI_TO_METER_UNIT ) );
}

Player::~Player( ) {
}

void Player::update( ) {
	switch ( _update_type ) {
	case UPDATE_TYPE_EYEONLY:
		actOnEyeOnly( );
		break;

	case UPDATE_TYPE_ALL:
		actOnPlayerAll( );
		break;
	}
}

void Player::setUpdateType( Player::UPDATE_TYPE type ) {
	_update_type = type;
}

void Player::onColliderEnter( ColliderConstPtr collider ) {

	OBJECT_TAG tag = collider->getTag( );

	// フロアの壁との接触
	if ( tag == OBJECT_TAG_WALL ) {
		adjustPosHitWall( collider );
	}

	// フロアのエレベーターのある壁との接触
	if ( tag == OBJECT_TAG_ELEVATOR_SIDE_WALL ) {
		adjustPosHitWall( collider );
	}

	// エレベーターの壁
	if ( tag == OBJECT_TAG_ELEVATOR_DOOR ) {
		adjustPosHitWall( collider );
	}

	// エレベーターに乗っている
	if ( tag == OBJECT_TAG_ELEVATOR ) {
		_elevator_box->requestRideOnElevator( &_ground_pos );
	}
}

FLOOR Player::getFloor( ) const {
	return _floor;
}

void Player::updatePos( ) {
	// 移動前座標の保存
	_past_pos = _ground_pos;
	
	_head_pos = _ground_pos + Vector( 0, PLAYER_HEIGHT, 0 );
}

void Player::walk( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	if ( keyboard->getKeyState( "W" ) ) {
		_ground_pos += Vector( _dir.x, 0, _dir.z ) *  PLAYER_MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "S" ) ) {
		_ground_pos += Vector( _dir.x, 0, _dir.z ) * -PLAYER_MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "A" ) ) {
		_ground_pos += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( ) *  PLAYER_MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "D" ) ) {
		_ground_pos += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( ) * -PLAYER_MOVE_SPEED;
	}

	// 前回サウンドを鳴らした距離から一定値で鳴らす
	Vector pos1 = _past_sound_pos;
	Vector pos2 = _ground_pos;
	pos1.y = 0;
	pos2.y = 0;
	if ( ( pos1 - pos2 ).getLength2( ) > WALK_SOUND_DISTANCE * WALK_SOUND_DISTANCE ) {
		SoundManager::getInstance( )->play( SoundManager::SE_WALK );
		_past_sound_pos = _ground_pos;
	}
}

void Player::actOnEyeOnly( ) {
	// 視線更新(コンソール非表示時)
	if ( !_console_active ) {
		updateDir( );
	}
	updateEye( );
}

void Player::actOnPlayerAll( ) {
	// 視線更新(コンソール非表示時)
	if ( !_console_active ) {
		updateDir( );
		walk( );
		updateEye( );
	}

	// 計算後の座標更新
	updatePos( );

	// フロア更新
	updateFloor( );

	// Listenerの更新
	updateEar( );
}

void Player::updateDir( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );
	Vector scr_center = Vector( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );

	// 中心からの距離にする
	pos -= scr_center;

	// 比率 -1 〜 0 〜 1
	double h_ratio = pos.x / scr_center.x;
	double v_ratio = pos.y / scr_center.y;

	// ラジアン
	double h_radian = h_ratio * MAX_H_RADIAN;
	double v_radian = v_ratio * MAX_V_RADIAN;

	Vector axis_v = _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) );
	Vector axis_h = _dir.cross( axis_v );
	Matrix h_mat = Matrix::makeTransformRotation( axis_h, h_radian );
	Matrix v_mat = Matrix::makeTransformRotation( axis_v, v_radian );

	// 正面にむける
	_dir = ( h_mat * v_mat ).multiply( _dir );

	// マウスカーソルを中心にする
	mouse->setMousePoint( ( int )scr_center.x, ( int )scr_center.y );
}

void Player::updateEye( ) {
	CameraPtr camera = Camera::getTask( );
	camera->setCamera( _head_pos * MIRI_TO_METER_UNIT, ( _head_pos + _dir ) * MIRI_TO_METER_UNIT );
}

void Player::updateEar( ) {
	SoundPtr sound = Sound::getTask( );
	sound->set3DSoundListener( _head_pos * MIRI_TO_METER_UNIT, ( _head_pos + _dir ) * MIRI_TO_METER_UNIT );
}

void Player::updateFloor( ) {
	_floor = ( FLOOR )( int )( fabs( _head_pos.y - FLOOR_HEIGHT ) / FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT );
}

void Player::adjustPosHitWall( ColliderConstPtr collider ) {
	SquareColliderConstPtr wall = std::dynamic_pointer_cast< const SquareCollider >( collider );
	Vector norm = wall->getNorm( );
	Vector wall_center = wall->getPos( );

	// 調整する方向を計算
	double dot = norm.dot( _past_pos - wall_center );
	int dir = ( dot > 0 ? 1 : -1 );

	// 超過した距離(半径を足した数)
	const double SPACE = 10.0;
	double dist = ( norm * dir * -1 ).dot( ( _ground_pos + ( norm * dir * -1 ) * PLAYER_COLLIDER_RADIUS ) - wall_center );
	dist += SPACE;

	_ground_pos = _ground_pos + ( norm * dir * dist );
}