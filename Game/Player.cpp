#include "Player.h"
#include "define.h"
#include "ElevatorBox.h"
#include "SquareCollider.h"
#include "UIActiveObservableComponent.h"
#include "SoundManager.h"

#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Sound.h"

// ���W�A�� = �x * �~���� / 180
const double MAX_H_RADIAN = 45 * PI / 180; // ��
const double MAX_V_RADIAN = 15 * PI / 180; // �c

const double PLAYER_MOVE_SPEED = 150.0;
const double PLAYER_HEIGHT = 1500.0;
const double PLAYER_COLLIDER_RADIUS = 500.0;
const double WALK_SOUND_DISTANCE = 1500.0; // ���̋����������特��炷

PTR( SphereCollider );
PTR( SquareCollider );

Player::Player( ElevatorBoxPtr elevator_box, UIActiveObservableComponentPtr ui_observable ) :
SphereCollider( _head_pos, PLAYER_COLLIDER_RADIUS, OBJECT_TAG_PLAYER ),
_ui_active( false ),
_ground_pos( 0, PLAYER_INIT_FLOOR * -FLOOR_TO_FLOOR_SPACE_AND_FLOOR_HEIGHT, 0 ),
_head_pos( 0, _ground_pos.y + PLAYER_HEIGHT, 0 ),
_sound_distance( 0 ),
_dir( 0, 0, 1 ),
_floor( PLAYER_INIT_FLOOR ),
_elevator_box( elevator_box ),
_update_type( UPDATE_TYPE_ALL ) {
	// �R���\�[�� or �q���g�̃A�N�e�B�u�ʒm���󂯎��
	ui_observable->subscribeOnActive( [ & ]( bool active ) { 
		_ui_active = active;
		// �R���\�[��������������}�E�X��^�񒆂ɍ��킹��
		if ( !_ui_active ) {
			Mouse::getTask( )->setMousePoint( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );
		}
	} );


	// �J���������ݒ�
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
		actOnAllControll( );
		break;

	case UPDATE_TYPE_GAMECLEAR:
		actOnGameClearControll( );
		break;
	}
}

void Player::setUpdateType( Player::UPDATE_TYPE type ) {
	_update_type = type;
	switch ( _update_type ) {
	case UPDATE_TYPE_EYEONLY:
		initEyeOnly( );
		break;
		
	case UPDATE_TYPE_ALL:
		initAllControll( );
		break;
		
	case UPDATE_TYPE_GAMECLEAR:
		initGameClearControll( );
		break;
	}
}

void Player::onColliderEnter( ColliderConstPtr collider ) {

	OBJECT_TAG tag = collider->getTag( );

	// �t���A�̕ǂƂ̐ڐG
	if ( tag == OBJECT_TAG_WALL ) {
		adjustPosHitWall( collider );
	}

	// �t���A�̃G���x�[�^�[�̂���ǂƂ̐ڐG
	if ( tag == OBJECT_TAG_ELEVATOR_SIDE_WALL ) {
		adjustPosHitWall( collider );
	}

	// �G���x�[�^�[�̕�
	if ( tag == OBJECT_TAG_ELEVATOR_DOOR ) {
		adjustPosHitWall( collider );
	}

	// �G���x�[�^�[�ɏ���Ă���
	if ( tag == OBJECT_TAG_ELEVATOR ) {
		_elevator_box->requestRideOnElevator( &_ground_pos );
	}
}

FLOOR Player::getFloor( ) const {
	return _floor;
}

void Player::updatePos( ) {
	// �ړ��O���W�̕ۑ�
	_past_pos = _ground_pos;
	
	_head_pos = _ground_pos + Vector( 0, PLAYER_HEIGHT, 0 );
}

void Player::walk( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	Vector dir;

	// �O���D��
	if ( keyboard->getKeyState( "W" ) ) {
		dir += Vector( _dir.x, 0, _dir.z );
	} else if ( keyboard->getKeyState( "S" ) ) {
		dir += Vector( _dir.x, 0, _dir.z ) * -1;
	}

	// ���E�����͎~�܂�
	if ( keyboard->getKeyState( "A" ) ) {
		dir += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( );
	}
	if ( keyboard->getKeyState( "D" ) ) {
		dir += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( ) * -1;
	}

	if ( dir != Vector( ) ) {
		_ground_pos += dir.normalize( ) * PLAYER_MOVE_SPEED;
		_sound_distance += ( _past_pos - _ground_pos ).getLength( );
	}

	// �O��T�E���h��炵������������l�Ŗ炷
	if ( _sound_distance > WALK_SOUND_DISTANCE ) {
		SoundManager::getInstance( )->play( SoundManager::SE_WALK );
		_sound_distance = 0;
	}
}

void Player::actOnEyeOnly( ) {
	// �����X�V(�R���\�[����\����)
	if ( !_ui_active ) {
		updateDir( );
	}
	updateEye( );
}

void Player::actOnAllControll( ) {
	// �����X�V(�R���\�[����\����)
	if ( !_ui_active ) {
		updateDir( );
		walk( );
	}

	// �v�Z��̍��W�X�V
	updatePos( );

	// �t���A�X�V
	updateFloor( );

	// Listener�̍X�V
	updateEar( );

	// �J�����̍X�V�͍Ō�
	if ( !_ui_active ) {
		updateEye( );
	}
}

void Player::actOnGameClearControll( ) {
	Vector goal = Vector( );
	Vector dir = ( goal - _ground_pos ).normalize( );
	const double SPEED = PLAYER_MOVE_SPEED * 0.1;

	_ground_pos += dir * SPEED;
	updatePos( );
	updateDir( );
	updateEye( );
	updateEar( );
}

void Player::initEyeOnly( ) {
	// ���ɂȂ�
}

void Player::initAllControll( ) {
	// ���ɂȂ�
}

void Player::initGameClearControll( ) {
	// �G���x�[�^�[�̐^�񒆒[�Ɉړ�������
	_ground_pos.x = ELEVATOR_INIT_X + ELEVATOR_WIDTH / 2;
	_ground_pos.y = 0;
	_ground_pos.z = ELEVATOR_INIT_Z;

	// ��������������
	Vector goal = Vector( );
	Vector dir = ( goal - _ground_pos ).normalize( );
	_dir = dir;
}

void Player::updateDir( ) {
	MousePtr mouse = Mouse::getTask( );
	Vector pos = mouse->getPoint( );
	Vector scr_center = Vector( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );

	// ���S����̋����ɂ���
	pos -= scr_center;

	// �䗦 -1 �` 0 �` 1
	double h_ratio = pos.x / scr_center.x;
	double v_ratio = pos.y / scr_center.y;

	// ���W�A��
	double h_radian = h_ratio * MAX_H_RADIAN;
	double v_radian = v_ratio * MAX_V_RADIAN;

	Vector axis_v = _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) );
	Vector axis_h = _dir.cross( axis_v );
	Matrix h_mat = Matrix::makeTransformRotation( axis_h, h_radian );
	Matrix v_mat = Matrix::makeTransformRotation( axis_v, v_radian );

	// ���ʂɂނ���
	_dir = ( h_mat * v_mat ).multiply( _dir );

	// �}�E�X�J�[�\���𒆐S�ɂ���
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

	// ��������������v�Z
	double dot = norm.dot( _past_pos - wall_center );
	int dir = ( dot > 0 ? 1 : -1 );

	// ���߂�������(���a�𑫂�����)
	const double SPACE = 10.0;
	double dist = ( norm * dir * -1 ).dot( ( _ground_pos + ( norm * dir * -1 ) * PLAYER_COLLIDER_RADIUS ) - wall_center );
	dist += SPACE;

	_ground_pos = _ground_pos + ( norm * dir * dist );
}