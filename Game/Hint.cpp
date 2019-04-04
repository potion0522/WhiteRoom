#include "Hint.h"
#include "QuestionManager.h"

#include "Drawer.h"
#include "Image.h"

const char* HINT_BG_FILEPATH = "Game/UI/UIBG.png";

Hint::Hint( QuestionManagerConstPtr question_manager ) :
_question_manager( question_manager ) {
	_bg = Drawer::getTask( )->getImage( HINT_BG_FILEPATH );
}

Hint::~Hint( ) {
}

void Hint::update( ) {
}

void Hint::draw( ) const {
	_bg->draw( );
}

void Hint::close( ) {
}

void Hint::open( ) {
}