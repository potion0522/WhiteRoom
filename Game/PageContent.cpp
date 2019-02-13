#include "PageContent.h"

PageContent::PageContent( const int& x, const int& y ) :
_x( x ),
_y( y ) {
}

PageContent::~PageContent( ) {
}

void PageContent::setCallback( std::function< void( ) > func ) {
	_func = func;
}
