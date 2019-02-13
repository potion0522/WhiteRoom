#include "Question1.h"

Question1::Question1( const int& x, const int& y, std::function< void( ) > func ) :
PageContent( x, y ) {
	setCallback( func );
}

Question1::~Question1( ) {
}

void Question1::update( ) {
}

void Question1::draw( ) const {
}
