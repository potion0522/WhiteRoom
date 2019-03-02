#include "PageContent.h"

PageContent::PageContent( const int& x, const int& y, std::function< void( ) > callback ) :
_x( x ),
_y( y ),
_callback( callback ) {
}

PageContent::~PageContent( ) {
}
