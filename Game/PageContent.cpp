#include "PageContent.h"
#include "SoundManager.h"

PageContent::PageContent( std::function< void( ) > callback ) :
_callback( callback ) {
}

PageContent::~PageContent( ) {
}

void PageContent::playClickSE( ) {
	SoundManager* sound = SoundManager::getInstance( );
	sound->play( SoundManager::SE_CONSOLE_CLICK );
}
