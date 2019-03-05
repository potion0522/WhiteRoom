#pragma once
#include "PageContent.h"
#include "smart_ptr.h"

PTR( QuestionManager );

class ConsoleQuestion : public PageContent {
public:
	ConsoleQuestion( const int& x, const int& y, std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion( );

public:
	virtual void update( ) = 0;
	virtual void draw( ) const = 0;

protected:
	QuestionManagerConstPtr  _question_manager;
};

