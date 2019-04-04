#pragma once
#include "UICanvas.h"
#include "smart_ptr.h"

PTR( Hint );
PTR( QuestionManager );
PTR( Image );

class Hint : public UICanvas {
public:
	Hint( QuestionManagerConstPtr );
	virtual ~Hint( );

public:
	void update( );
	void draw( ) const;
	void close( );
	void open( );

private:
	QuestionManagerConstPtr _question_manager;
	ImagePtr _bg;
};

