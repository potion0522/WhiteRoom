#include "PageContent.h"

PageContent::PageContent( std::function< void( ) > callback ) :
_callback( callback ) {
}

PageContent::~PageContent( ) {
}
