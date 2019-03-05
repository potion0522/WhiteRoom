#include "ConsoleQuestion1.h"

ConsoleQuestion1::ConsoleQuestion1( const int& x, const int& y, std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
ConsoleQuestion( x, y, callback, question_manager ) {
}

ConsoleQuestion1::~ConsoleQuestion1( ) {
}

void ConsoleQuestion1::update( ) {
}

void ConsoleQuestion1::draw( ) const {
}