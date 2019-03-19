#include "ConsoleQuestion5.h"
#include "QuestionManager.h"

#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"

ConsoleQuestion5::ConsoleQuestion5( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( callback, question_manager ) {
}

ConsoleQuestion5::~ConsoleQuestion5( ) {
}

void ConsoleQuestion5::draw( int x, int y ) const {
}

void ConsoleQuestion5::actOnNone( ) {
}

void ConsoleQuestion5::actOnPush( ) {
}

void ConsoleQuestion5::actOnPushUp( ) {
}

void ConsoleQuestion5::actOnAnswer( ) {
}