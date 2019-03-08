#pragma once
#include "smart_ptr.h"
#include "define.h"
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
	void drawQuestion2Hint( ) const;

private:
	void addDockingSphere( OBJECT_TAG tag );
	void dockingSphere( OBJECT_TAG tag1, OBJECT_TAG tag2 );

private:
	FLOOR _floor;
	std::map< OBJECT_TAG, Question2SpherePtr > _spheres;
	std::vector< OBJECT_TAG > _docking_sphere;
	CollideManagerPtr _collide_manager;
};