#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include "SphereCollider.h"

/******************************************************************

球体そのもののクラス
エレベーターがある場合、当たり判定が消えるので壁の判定は独自で行う

******************************************************************/


PTR( Model );

class Sphere : public SphereCollider {
public:
	Sphere( Vector pos, double radius, unsigned char color_idx = SPHERE_COLOR_WHITE, OBJECT_TAG tag = OBJECT_TAG_SPHERE );
	virtual ~Sphere( );

public:
	void update( );
	void draw( ) const;
	virtual void onColliderEnter( ColliderConstPtr collider );

private:
	void adjustInFloor( ); // 壁に埋まった時の強制脱出
	void setSpeed( const Vector& speed );
	void refrection( ); // 壁反射
	void move( );
	Vector getRefrectionVector( const Vector& wall_norm );

private:
	static const int DIV_NUM = 24;
	const Vector INIT_POS;

protected:
	int _exist_inside_last_time;
	ModelPtr _model;
	Vector _pos;
	Vector _past_pos;
	Vector _speed;
	Matrix _rot;
	double _radius;
};

