#include "ConsoleQuestion.h"

ConsoleQuestion::ConsoleQuestion( std::function< void( ) > callback, QuestionManagerConstPtr question_manager ) :
PageContent( callback ),
_question_manager( question_manager ) {
}

ConsoleQuestion::~ConsoleQuestion( ) {
}
