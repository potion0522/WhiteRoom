#pragma once
#include "smart_ptr.h"
#include "define.h"
#include "Mathematics.h"
#include <map>
#include <vector>

/***********************************************

Question2のフロア用ヒントを作成するクラス

***********************************************/


PTR( Model );
PTR( QuestionManager );
PTR( Question2Sphere );
PTR( CollideManager );

class Question2FloorHint {
public:
	Question2FloorHint( QuestionManagerConstPtr question_manager, CollideManagerPtr collide_manager, FLOOR floor );
	virtual ~Question2FloorHint( );

public:
	void update( );
	void draw( ) const;

private:
	void addDockingSphere( OBJECT_TAG tag );
	void dockingSphere( OBJECT_TAG tag1, OBJECT_TAG tag2 );
	void generateSphere( OBJECT_TAG tag, const Vector& pos );

private:
	FLOOR _floor;
	unsigned char _sphere_color_idx;
	std::map< OBJECT_TAG, Question2SpherePtr > _spheres;
	std::vector< OBJECT_TAG > _docking_sphere;
	CollideManagerPtr _collide_manager;
	QuestionManagerConstPtr _question_manager;
};