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
	Sphere( Vector pos, double radius, OBJECT_TAG tag = OBJECT_TAG_SPHERE );
	virtual ~Sphere( );

public:
	void update( );
	void draw( ) const;
	virtual void onColliderEnter( ColliderConstPtr collider );

private:
	void generate( );
	void adjustInFloor( ); // 壁に埋まった時の強制脱出
	void setSpeed( const Vector& speed );
	void refrection( ); // 壁反射
	void move( );
	Vector getRefrectionVector( const Vector& wall_norm );

private:
	static const int _DIV_NUM = 24;

protected:
	ModelPtr _model;
	Vector _pos;
	Vector _past_pos;
	Vector _speed;
	Matrix _rot;
	double _radius;
};

