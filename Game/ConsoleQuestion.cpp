#include "ConsoleQuestion.h"

ConsoleQuestion::ConsoleQuestion( const int& x, const int& y, std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
PageContent( x, y, callback ),
_question_manager( question_manager ) {
}

ConsoleQuestion::~ConsoleQuestion( ) {
}
