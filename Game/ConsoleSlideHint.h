#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

/*************************************************************

�R���\�[�����X���C�h�ł��邱�Ƃ�`���邽�߂̃q���g��
�ݒu���邽�߂̃N���X

*************************************************************/

PTR( ConsoleSlideHint );
PTR( Model );

class ConsoleSlideHint {
public:
	ConsoleSlideHint( const Vector& pos, Matrix& rot );
	virtual ~ConsoleSlideHint( );

public:
	void draw( ) const;

private:
	Vector _pos;
	Matrix _rot;
	ModelPtr _model;
};

