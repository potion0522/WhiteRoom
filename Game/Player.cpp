#include "Player.h"
#include "define.h"
#include "SquareCollider.h"

#include "Camera.h"
#include "Mouse.h"
#include "Keyboard.h"

// ���W�A�� = �x * �~���� / 180
const double MAX_H_RADIAN = 45 * PI / 180; // ��
const double MAX_V_RADIAN = 15 * PI / 180; // �c

const double MOVE_SPEED = 100;


// ���ƂŊO���t�@�C���ɂ���
const double HEIGHT = FLOOR_HEIGHT / 2;
const double COLLIDER_SIZE = 1000.0;

Player::Player( ) :
SphereCollider( _head_pos, COLLIDER_SIZE, OBJECT_TAG_PLAYER ),
_HEIGHT( HEIGHT ),
_PLAYER_COLLIDER_RADIUS( COLLIDER_SIZE ),
_ground_pos( ),
_head_pos( 0, _HEIGHT, 0 ),
_dir( 0, 0, 1 ),
_floor( FLOOR_GF ),
_elevator_floor( FLOOR_GF ),
_elevator_moving( false ) {
	CameraPtr camera = Camera::getTask( );
	camera->setCamera( _head_pos, _dir );
	camera->setCameraUp( Vector( 0, 1, 0 ) );
	camera->setNearFar( 1 * ( float )MIRI_TO_METER_UNIT, FLOOR_WIDTH );
}

Player::~Player( ) {
}

void Player::update( ) {
	// �ړ��O���W�̕ۑ�
	_past_pos = _ground_pos;

	// �����X�V
	updateDir( );

	// �ړ�
	updatePos( );

	// �J�����̍X�V
	updateEye( );
}

void Player::onColliderEnter( ColliderConstPtr collider ) {

	OBJECT_TAG tag = collider->getTag( );

	// �t���A�̕ǂƂ̐ڐG
	if ( tag == OBJECT_TAG_WALL ) {
		adjustPosHitWall( collider );
	}

	// �t���A�̃G���x�[�^�[�̂���ǂƂ̐ڐG
	if ( tag == OBJECT_TAG_ELEVATOR_SIDE_WALL ) {
		// �����̃t���A�ƃG���x�[�^�[�̃t���A���ꏏ�Ȃ牽�����Ȃ�
		if ( _elevator_floor != _floor || _elevator_moving ) {
			adjustPosHitWall( collider );
		}
	}

	// �G���x�[�^�[�̕�
	if ( tag == OBJECT_TAG_ELEVATOR_DOOR ) {
		if ( _elevator_moving ) {
			adjustPosHitWall( collider );
		}
	}
}

void Player::announceArrive( int floor ) {
	_elevator_floor = ( FLOOR )floor;
	_elevator_moving = false;
}

void Player::announceMove( ) {
	_elevator_moving = true;
}

void Player::updatePos( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	if ( keyboard->getKeyState( "W" ) ) {
		_ground_pos += Vector( _dir.x, 0, _dir.z ) *  MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "S" ) ) {
		_ground_pos += Vector( _dir.x, 0, _dir.z ) * -MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "A" ) ) {
		_ground_pos += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( ) *  MOVE_SPEED;
	}
	if ( keyboard->getKeyState( "D" ) ) {
		_ground_pos += _dir.cross( Vector( _dir.x, _dir.y + 100, _dir.z ) ).normalize( ) * -MOVE_SPEED;
	}
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
	_head_pos = _ground_pos + Vector( 0, _HEIGHT, 0 );

	CameraPtr camera = Camera::getTask( );
	camera->setCamera( _head_pos * MIRI_TO_METER_UNIT, ( _head_pos + _dir ) * MIRI_TO_METER_UNIT );
}

void Player::adjustPosHitWall( ColliderConstPtr collider ) {
	SquareColliderConstPtr wall = std::dynamic_pointer_cast< const SquareCollider >( collider );
	Vector norm = wall->getNorm( );
	Vector wall_center = wall->getPos( );

	// ��������������v�Z
	double dot = norm.dot( _past_pos - wall_center );
	int dir = ( dot > 0 ? 1 : -1 );

	// ���߂�������(���a�𑫂�����)
	double dist = ( norm * dir * -1 ).dot( ( _ground_pos + ( norm * dir * -1 ) * _PLAYER_COLLIDER_RADIUS ) - wall_center );

	_ground_pos = _ground_pos + ( norm * dir * dist );
}