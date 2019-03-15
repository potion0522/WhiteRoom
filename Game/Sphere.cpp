#include "Sphere.h"
#include "define.h"

#include "Mathematics.h"
#include "Model.h"
#include "Drawer.h"

PTR( SphereCollider );

const double MAX_SPEED = 400.0;
const double IDLE_SPEED = 50.0; // 止まっていると判定する速度
const double OBJECT_REFRECT_SPEED = 200.0; // オブジェクト同士の衝突時の速度
const double BRAKE = 0.85;

Sphere::Sphere( Vector pos, double radius, OBJECT_TAG tag ) :
SphereCollider( _pos, radius, tag ),
_pos( pos ),
_radius( radius ) {
	generate( );
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
	OBJECT_TAG tag = collider->getTag( );

	// 特定のオブジェクト以外とぶつかった時
	if ( tag != OBJECT_TAG_ELEVATOR &&
		 tag != OBJECT_TAG_ELEVATOR_DOOR &&
		 tag != OBJECT_TAG_ELEVATOR_SIDE_WALL &&
		 tag != OBJECT_TAG_WALL &&
		 tag != OBJECT_TAG_NONE
		) {
		Vector dir = ( _pos - collider->getPos( ) ).normalize( );
		dir.y = 0; // yは考慮しない

		Vector refrection_vector = getRefrectionVector( dir );
		
		double now_speed = _speed.getLength2( );
		// オブジェクトが静止しているか、動いているかで処理を分ける
		if ( now_speed > IDLE_SPEED * IDLE_SPEED ) {
			Vector vec = ( refrection_vector + _speed.normalize( ) ).normalize( );
			setSpeed( vec * _speed.getLength( ) * BRAKE );
		} else {
			setSpeed( dir * OBJECT_REFRECT_SPEED );
		}
	}
}


void Sphere::generate( ) {
	// 球を縦横にDIV_NUM(半分)分割して回転を使用して頂点を求める

	_model = ModelPtr( new Model );
	_model->alloc( _DIV_NUM * _DIV_NUM * 4 );
	_model->setTexture( Drawer::getTask( )->getImage( "Game/Texture/TextureWhite.png" ) );

	// 縦
	for ( int i = 0; i < _DIV_NUM; i++ ) {
		Vector vec1 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / _DIV_NUM * ( i + 0 ) ).multiply( Vector( 0, _radius, 0 ) );
		Vector vec2 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / _DIV_NUM * ( i + 1 ) ).multiply( Vector( 0, _radius, 0 ) );
		double y1 = vec1.y;
		double y2 = vec2.y;
		double r1 = fabs( vec1.z );
		double r2 = fabs( vec2.z );

		// 横
		for ( int j = 0; j < _DIV_NUM * 2; j++ ) {
			Matrix rot1 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / ( _DIV_NUM * 2 ) * ( ( j + 0 ) % ( _DIV_NUM * 2 ) ) );
			Matrix rot2 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / ( _DIV_NUM * 2 ) * ( ( j + 1 ) % ( _DIV_NUM * 2 ) ) );

			Vector ver_pos[ 4 ] = {
				rot1.multiply( Vector( 0, y1, r1 ) ), // 左上
				rot2.multiply( Vector( 0, y1, r1 ) ), // 右上
				rot1.multiply( Vector( 0, y2, r2 ) ), // 左下
				rot2.multiply( Vector( 0, y2, r2 ) ), // 右下
			};


			float u1 = ( float )( j % _DIV_NUM + 0 ) / _DIV_NUM;
			float u2 = ( float )( j % _DIV_NUM + 1 ) / _DIV_NUM;

			float v1 = ( float )( ( y1 + _radius ) / ( _radius * 2 ) );
			float v2 = ( float )( ( y2 + _radius ) / ( _radius * 2 ) );

			Model::Vertex ver[ 4 ] = {
				Model::Vertex( ver_pos[ 0 ], u1, v1, ver_pos[ 0 ] ),
				Model::Vertex( ver_pos[ 1 ], u2, v1, ver_pos[ 1 ] ),
				Model::Vertex( ver_pos[ 2 ], u1, v2, ver_pos[ 2 ] ),
				Model::Vertex( ver_pos[ 3 ], u2, v2, ver_pos[ 3 ] ),
			};

			int idx = ( i * _DIV_NUM * 2 + j ) * 6;
			_model->setVertex( idx + 0, ver[ 0 ] );
			_model->setVertex( idx + 1, ver[ 1 ] );
			_model->setVertex( idx + 2, ver[ 2 ] );

			_model->setVertex( idx + 3, ver[ 1 ] );
			_model->setVertex( idx + 4, ver[ 3 ] );
			_model->setVertex( idx + 5, ver[ 2 ] );

		}
	}
}

void Sphere::adjustInFloor( ) {
	// 止まるまでは何もしない
	if ( _speed.getLength2( ) > IDLE_SPEED * IDLE_SPEED ) {
		return;
	}

	const int HALF_WIDTH = FLOOR_WIDTH / 2;
	// z+
	if ( _pos.z > ( HALF_WIDTH - _radius ) *  1 ) {
		_pos.z = ( HALF_WIDTH - _radius ) * 1;
	}

	// z-
	if ( _pos.z < ( HALF_WIDTH - _radius ) * -1 ) {
		_pos.z = ( HALF_WIDTH - _radius ) * -1;
	}
	
	// x+
	if ( _pos.x > ( HALF_WIDTH - _radius ) *  1 ) {
		_pos.x = ( HALF_WIDTH - _radius ) * 1;
	}
	
	// x-
	if ( _pos.x < ( HALF_WIDTH - _radius ) * -1 ) {
		_pos.x = ( HALF_WIDTH - _radius ) * -1;
	}
}

void Sphere::setSpeed( const Vector& speed ) {
	_speed += speed;
}

void Sphere::refrection( ) {
	const int HALF_WIDTH = FLOOR_WIDTH / 2;
	Vector refrection_vector = Vector( );
	// z+
	if ( _pos.z > ( HALF_WIDTH - _radius ) *  1 ) {
		refrection_vector = getRefrectionVector( Vector( 0, 0, -1 ) );
	}

	// z-
	if ( _pos.z < ( HALF_WIDTH - _radius ) * -1 ) {
		refrection_vector = getRefrectionVector( Vector( 0, 0, 1 ) );
	}
	
	// x+
	if ( _pos.x > ( HALF_WIDTH - _radius ) *  1 ) {
		refrection_vector = getRefrectionVector( Vector( 1, 0, 0 ) );
	}
	
	// x-
	if ( _pos.x < ( HALF_WIDTH - _radius ) * -1 ) {
		refrection_vector = getRefrectionVector( Vector( -1, 0, 0 ) );
	}

	
	if ( refrection_vector != Vector( ) ) {
		_speed = refrection_vector.normalize( ) * _speed.getLength( );
	}
}

void Sphere::move( ) {
	Vector dir = _speed.normalize( );
	if ( _speed.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
		_speed = dir * MAX_SPEED;
	}
	_past_pos = _pos;
	_pos += _speed;
	_speed *= BRAKE;
}

Vector Sphere::getRefrectionVector( const Vector& wall_norm ) {
	// 反射ベクトル(R)　= F + 2( -F dot N ) * N

	Vector F = _speed;
	Vector N = wall_norm;

	Vector R = F + N * ( -F.dot( N ) ) * 2;
	return R;
}