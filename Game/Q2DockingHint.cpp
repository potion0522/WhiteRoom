#include "Q2DockingHint.h"
#include "define.h"

#include "Model.h"
#include "Drawer.h"

const char* Q2_DOCKING_HINT_TEXTURE = "Game/Texture/Q2DockingHint.png";

Q2DockingHint::Q2DockingHint( const Vector& pos, const Matrix& rot ) :
_pos( pos ),
_rot( rot ) {
	_model = ModelPtr( new Model );
	_model->setTexture( Drawer::getTask( )->getImage( Q2_DOCKING_HINT_TEXTURE ) );
	_model->alloc( 2 );

	// 4 : 1
	const double WIDTH  = FLOOR_WIDTH / 2;
	const double HEIGHT = 1 / 4.0 * WIDTH;
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

Q2DockingHint::~Q2DockingHint( ) {
}

void Q2DockingHint::draw( ) const {
	_model->draw( _pos * MIRI_TO_METER_UNIT, _rot );
}