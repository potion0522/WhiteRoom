#include "Player.h"
#include "define.h"

#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"

// ラジアン = 度 * 円周率 / 180
const double MAX_H_RADIAN = 45 * PI / 180; // 横
const double MAX_V_RADIAN = 15 * PI / 180; // 縦

const double MOVE_SPEED = 100;

Player::Player( ) :
_PLAYER_COLLIDER_RADIUS( 500 ),
_HEIGHT( 1500 ),
SphereCollider( _head_pos, _PLAYER_COLLIDER_RADIUS, OBJECT_TAG_PLAYER ),
_stand_pos( ),
_head_pos( 0, _HEIGHT, 0 ),
_dir( 0, 0, 1 ) {
	CameraPtr camera = Camera::getTask( );
	camera->setCamera( _head_pos, _dir );
	camera->setCameraUp( Vector( 0, 1, 0 ) );
}

Player::~Player( ) {
}

void Player::update( ) {
	// 移動前座標の保存
	_past_pos = _stand_pos;

	// 視線更新
	updateDir( );

	// 移動
	updatePos( );

	// カメラの更新
	updateEye( );
}

void Player::onColliderEnter( ColliderConstPtr collider ) {
	if ( collider->getTag( ) == OBJECT_TAG_WALL ) {
		_stand_pos = Vector( );
	}
}

void Player::updatePos( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	if ( keyboard->getKeyState( "W" ) ) {
		_stand_pos += Vector( _dir.x, 0, _dir.z ) *  MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "S" ) ) {
		_stand_pos += Vector( _dir.x, 0, _dir.z ) * -MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "A" ) ) {
		_stand_pos += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( ) *  MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "D" ) ) {
		_stand_pos += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( ) * -MOVE_SPEED;
	}
}

void Player::updateDir( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );
	Vector scr_center = Vector( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );

	// 中心からの距離にする
	pos -= scr_center;

	// 比率 -1 ～ 0 ～ 1
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
	_head_pos = _stand_pos + Vector( 0, _HEIGHT, 0 );

	CameraPtr camera = Camera::getTask( );
	camera->setCamera( _head_pos * MIRI_TO_METER_UNIT, ( _head_pos + _dir ) * MIRI_TO_METER_UNIT );
}
