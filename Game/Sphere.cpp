#include "Sphere.h"
#include "define.h"

#include "Mathematics.h"
#include "Model.h"
#include "Drawer.h"

Sphere::Sphere( Vector pos, double radius ) :
_pos( pos ),
_radius( radius ) {
	generate( );
}

Sphere::~Sphere( ) {
}

void Sphere::draw( ) const {
	_model->draw( _pos );
}

void Sphere::generate( ) {
	// ðc¡ÉDIV_NUM(¼ª)ªµÄñ]ðgpµÄ¸_ðßé

	_model = ModelPtr( new Model );
	_model->alloc( _DIV_NUM * _DIV_NUM * 4 );
	_model->setTexture( Drawer::getTask( )->getImage( "Game/Texture/TextureWhite.png" ) );

	// c
	for ( int i = 0; i < _DIV_NUM; i++ ) {
		Vector r1 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / _DIV_NUM * ( ( i + 0 ) % _DIV_NUM ) ).multiply( Vector( 0, _radius, 0 ) );
		Vector r2 = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / _DIV_NUM * ( ( i + 1 ) % _DIV_NUM ) ).multiply( Vector( 0, _radius, 0 ) );

		// ¡
		for ( int j = 0; j < _DIV_NUM * 2; j++ ) {
			Matrix rot1 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / _DIV_NUM * 2 * ( ( j + 0 ) % ( _DIV_NUM * 2 ) ) );
			Matrix rot2 = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / _DIV_NUM * 2 * ( ( j + 1 ) % ( _DIV_NUM * 2 ) ) );

			Vector ver_pos[ 4 ] = {
				rot1.multiply( r1 ) * MIRI_TO_METER_UNIT, // ¶ã
				rot2.multiply( r1 ) * MIRI_TO_METER_UNIT, // Eã
				rot1.multiply( r2 ) * MIRI_TO_METER_UNIT, // ¶º
				rot2.multiply( r2 ) * MIRI_TO_METER_UNIT, // Eº
			};

			Model::Vertex ver[ 4 ] = {
				Model::Vertex( ver_pos[ 0 ], 0, 0, ver_pos[ 0 ] ),
				Model::Vertex( ver_pos[ 1 ], 0, 0, ver_pos[ 1 ] ),
				Model::Vertex( ver_pos[ 2 ], 0, 0, ver_pos[ 2 ] ),
				Model::Vertex( ver_pos[ 3 ], 0, 0, ver_pos[ 3 ] ),
			};

			int idx = ( i * _DIV_NUM * 2 + j ) * 6;
			_model->setVertex( idx + 0, ver[ 0 ] );
			_model->setVertex( idx + 1, ver[ 1 ] );
			_model->setVertex( idx + 2, ver[ 2 ] );

			_model->setVertex( idx + 3, ver[ 1 ] );
			_model->setVertex( idx + 4, ver[ 3 ] );
			_model->setVertex( idx + 5, ver[ 2 ] );

		}
	}
}
