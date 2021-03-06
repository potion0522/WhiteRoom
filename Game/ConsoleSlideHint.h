#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

/*************************************************************

コンソールがスライドできることを伝えるためのヒントを
設置するためのクラス

*************************************************************/

PTR( ConsoleSlideHint );
PTR( Model );

class ConsoleSlideHint {
public:
	ConsoleSlideHint( const Vector& pos, const Matrix& rot );
	virtual ~ConsoleSlideHint( );

public:
	void draw( ) const;

private:
	Vector _pos;
	Matrix _rot;
	ModelPtr _model;
};

