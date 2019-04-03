#include "Sphere.h"
#include "define.h"

#include "Mathematics.h"
#include "Model.h"
#include "Drawer.h"
#include "Manager.h"
#include "Random.h"

PTR( SphereCollider );

const double MAX_SPEED = 400.0;
const double IDLE_SPEED = 50.0; // 止まっていると判定する速度
const double SPHERE_INSIDE_PUSH_POWER = 50.0;
const double OBJECT_REFRECT_SPEED = 200.0; // オブジェクト同士の衝突時の速度
const double BRAKE = 0.85;
const int SPHERE_POS_INIT_TIME = 10000;

Sphere::Sphere( Vector pos, double radius, unsigned char color_idx, OBJECT_TAG tag ) :
SphereCollider( _pos, radius, tag ),
INIT_POS( pos ),
_pos( pos ),
_radius( radius ),
_exist_inside_last_time( 0 ) {
	// 球を縦横にDIV_NUM(半分)分割して回転を使用して頂点を求める

	_model = ModelPtr( new Model );
	_model->alloc( DIV_NUM * DIV_NUM * 4 );
	_model->setTexture( Drawer::getTask( )->getImage( "Game/Texture/TextureWhite.png" ) );

	Model::Color color;
	switch ( color_idx ) {
		case SPHERE_COLOR_RED:
			color = Model::Color( 255, 0, 0, 255 );
			break;
		case SPHERE_COLOR_GREEN:
			color = Model::Color( 0, 255, 0, 255 );
			break;
		case SPHERE_COLOR_BLUE:
			color = Model::Color( 0, 0, 255, 255 );
			break;
		case SPHERE_COLOR_WHITE:
			color = Model::Color( 255, 255, 255, 255 );
			break;
		default:
			color = Model::Color( 255, 255, 255, 255 );
			break;
	}

	// 縦
	for ( int i = 0; i < DIV_NUM; i++ ) {
		Vector vec1 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / DIV_NUM * ( i + 0 ) ).multiply( Vector( 0, _radius, 0 ) );
		Vector vec2 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / DIV_NUM * ( i + 1 ) ).multiply( Vector( 0, _radius, 0 ) );
		double y1 = vec1.y;
		double y2 = vec2.y;
		double r1 = fabs( vec1.z );
		double r2 = fabs( vec2.z );

		// 横
		for ( int j = 0; j < DIV_NUM * 2; j++ ) {
			Matrix rot1 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / ( DIV_NUM * 2 ) * ( ( j + 0 ) % ( DIV_NUM * 2 ) ) );
			Matrix rot2 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / ( DIV_NUM * 2 ) * ( ( j + 1 ) % ( DIV_NUM * 2 ) ) );

			Vector ver_pos[ 4 ] = {
				rot1.multiply( Vector( 0, y1, r1 ) ), // 左上
				rot2.multiply( Vector( 0, y1, r1 ) ), // 右上
				rot1.multiply( Vector( 0, y2, r2 ) ), // 左下
				rot2.multiply( Vector( 0, y2, r2 ) ), // 右下
			};


			float u1 = ( float )( j % DIV_NUM + 0 ) / DIV_NUM;
			float u2 = ( float )( j % DIV_NUM + 1 ) / DIV_NUM;

			float v1 = ( float )( ( y1 + _radius ) / ( _radius * 2 ) );
			float v2 = ( float )( ( y2 + _radius ) / ( _radius * 2 ) );

			Model::Vertex ver[ 4 ] = {
				Model::Vertex( ver_pos[ 0 ], u1, v1, ver_pos[ 0 ], color ),
				Model::Vertex( ver_pos[ 1 ], u2, v1, ver_pos[ 1 ], color ),
				Model::Vertex( ver_pos[ 2 ], u1, v2, ver_pos[ 2 ], color ),
				Model::Vertex( ver_pos[ 3 ], u2, v2, ver_pos[ 3 ], color ),
			};

			int idx = ( i * DIV_NUM * 2 + j ) * 6;
			_model->setVertex( idx + 0, ver[ 0 ] );
			_model->setVertex( idx + 1, ver[ 1 ] );
			_model->setVertex( idx + 2, ver[ 2 ] );

			_model->setVertex( idx + 3, ver[ 1 ] );
			_model->setVertex( idx + 4, ver[ 3 ] );
			_model->setVertex( idx + 5, ver[ 2 ] );

		}
	}
}

Sphere::~Sphere( ) {
}

void Sphere::update( ) {
	move( );
	refrection( );
	adjustInFloor( );
	
	// 回転
	Vector move = ( _pos - _past_pos );
	double circumference = _radius * 2 * PI;
	double angle = move.getLength( ) * PI2 / circumference;
	_rot *= Matrix::makeTransformRotation( move.cross( Vector( 0, 1, 0 ) ), angle );
}

void Sphere::draw( ) const {
	// 縮小
	Matrix scall = Matrix::makeTransformScaling( Vector( MIRI_TO_METER_UNIT, MIRI_TO_METER_UNIT, MIRI_TO_METER_UNIT ) );


	_model->draw( _pos * MIRI_TO_METER_UNIT, scall * _rot );
}

void Sphere::onColliderEnter( ColliderConstPtr collider ) {

	Collider::TYPE type = collider->getType( );
	switch ( type ) {
		case Collider::TYPE_SPHERE : {
			Vector other_to_this_vec = ( _pos - collider->getPos( ) );
			other_to_this_vec.y = 0; // y は考慮しない

			Vector ref = other_to_this_vec.normalize( ) * OBJECT_REFRECT_SPEED + _speed;

			setSpeed( ref );
		} break;

		case Collider::TYPE_SQUARE: // 壁は範囲が決まっているため個々に行わない
			break;
	}
}

void Sphere::adjustInFloor( ) {
	int now = Manager::getInstance( )->getNowCount( );

	// 一定以上の時間外側にいたら位置をリセット(緊急措置)
	if ( now - _exist_inside_last_time > SPHERE_POS_INIT_TIME ) {
		_pos = INIT_POS;
		setSpeed( Vector( ) );
	}
}

void Sphere::setSpeed( const Vector& speed ) {
	_speed = speed;
}

void Sphere::refrection( ) {
	const int HALF_WIDTH = FLOOR_WIDTH / 2;
	const double ADJUST_RANGE = HALF_WIDTH - _radius;
	Vector refrection_norm = Vector( );

	// z+
	if ( _pos.z >= ADJUST_RANGE *  1 ) {
		refrection_norm = Vector( 0, 0, -1 );
	}
	// z-
	if ( _pos.z <= ADJUST_RANGE * -1 ) {
		refrection_norm = Vector( 0, 0, 1 );
	}
	// x+
	if ( _pos.x >= ADJUST_RANGE *  1 ) {
		refrection_norm = Vector( -1, 0, 0 );
	}
	// x-
	if ( _pos.x <= ADJUST_RANGE * -1 ) {
		refrection_norm = Vector(  1, 0, 0 );
	}
	
	if ( refrection_norm != Vector( ) ) {
		Vector refrection_vector = refrection_norm;
		Vector speed = refrection_norm * SPHERE_INSIDE_PUSH_POWER;

		// 動いているなら反射ベクトルを適用
		if ( _speed.getLength2( ) > IDLE_SPEED * IDLE_SPEED ) {
			refrection_vector = getRefrectionVector( refrection_norm );
			speed = _speed;
		}

		setSpeed( refrection_vector.normalize( ) * speed.getLength( ) );
	} else {
		_exist_inside_last_time = Manager::getInstance( )->getNowCount( );
	}
}

void Sphere::move( ) {
	Vector dir = _speed.normalize( );
	if ( _speed.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		_speed = dir * MAX_SPEED;
	}
	_past_pos = _pos;
	_pos += _speed;
	setSpeed( _speed * BRAKE );
}

Vector Sphere::getRefrectionVector( const Vector& wall_norm ) {
	// 反射ベクトル(R)　= F + 2( -F dot N ) * N

	Vector F = _speed;
	Vector N = wall_norm;

	Vector R = F + N * ( -F.dot( N ) ) * 2;
	return R;
}