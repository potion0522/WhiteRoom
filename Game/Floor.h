#pragma once
#include "smart_ptr.h"

PTR( Floor );
PTR( Model );

/*

	�K�w�P�ʂŊǗ�����N���X
	�ǂȂǂ̃|���S�������g�ŕ`��

*/

class Floor {
public:
	Floor( double y );
	virtual ~Floor( );

public:
	double getY( ) const;

	void draw( ) const;

private:
	void generateRoom( );

private:
	double _y;

	ModelPtr _floor;
};

