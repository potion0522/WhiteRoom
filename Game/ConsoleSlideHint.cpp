#include "ConsoleSlideHint.h"
#include "define.h"

#include "Model.h"
#include "Drawer.h"

const char* SLIDE_HINT_TEXTURE = "Game/Texture/SlideHint.png";

ConsoleSlideHint::ConsoleSlideHint( const Vector& pos, Matrix& rot ) :
_pos( pos ),
_rot( rot ) {
	_model = ModelPtr( new Model );
	_model->setTexture( Drawer::getTask( )->getImage( SLIDE_HINT_TEXTURE ) );
	_model->alloc( 2 );

	// 16 : 9
	const double WIDTH  = 1000;
	const double HEIGHT = 9.0 / 16.0 * WIDTH;
	const Vector NORM = Vector( 0, 1 );

	Vector vert_pos[ 4 ] = {
		Vector( -WIDTH / 2,  HEIGHT / 2 ) * MIRI_TO_METER_UNIT, // ¶ã
		Vector(  WIDTH / 2,  HEIGHT / 2 ) * MIRI_TO_METER_UNIT, // ‰Eã
		Vector( -WIDTH / 2, -HEIGHT / 2 ) * MIRI_TO_METER_UNIT, // ¶‰º
		Vector(  WIDTH / 2, -HEIGHT / 2 ) * MIRI_TO_METER_UNIT, // ‰E‰º
	};
	Model::Vertex vert[ 4 ] = {
		Model::Vertex( vert_pos[ 0 ], 0, 0, NORM ),
		Model::Vertex( vert_pos[ 1 ], 1, 0, NORM ),
		Model::Vertex( vert_pos[ 2 ], 0, 1, NORM ),
		Model::Vertex( vert_pos[ 3 ], 1, 1, NORM ),
	};

	_model->setVertex( 0, vert[ 0 ] );
	_model->setVertex( 1, vert[ 1 ] );
	_model->setVertex( 2, vert[ 2 ] );

	_model->setVertex( 3, vert[ 1 ] );
	_model->setVertex( 4, vert[ 3 ] );
	_model->setVertex( 5, vert[ 2 ] );
}

ConsoleSlideHint::~ConsoleSlideHint( ) {
}

void ConsoleSlideHint::draw( ) const {
	_model->draw( _pos * MIRI_TO_METER_UNIT, _rot );
}