#pragma once
#include "Scene.h"
#include "smart_ptr.h"

PTR( SceneTitle );
PTR( Image );
PTR( Button );

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );

public:
	void update( );
	void draw( ) const;

private:
	void updateButton( );
	void updateFontFlash( );

private:
	const double FONT_FLASHING_RATIO;
	const int FONT_FLASHING_ALPHA;
	int _count;

	ImagePtr _bg;
	ButtonPtr _click_to_start_font;
};

