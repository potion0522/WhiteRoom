#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"
#include "SphereCollider.h"

/******************************************************************

���̂��̂��̂̃N���X
�G���x�[�^�[������ꍇ�A�����蔻�肪������̂ŕǂ̔���͓Ǝ��ōs��

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
	void adjustInFloor( ); // �ǂɖ��܂������̋����E�o
	void setSpeed( const Vector& speed );
	void refrection( ); // �ǔ���
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

