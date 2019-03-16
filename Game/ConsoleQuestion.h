#pragma once
#include "PageContent.h"
#include "smart_ptr.h"

/************************************************

�R���\�[���̖��𓚗��̃x�[�X�N���X

************************************************/

PTR( QuestionManager );

class ConsoleQuestion : public PageContent {
public:
	ConsoleQuestion( std::function< void( ) > callback, QuestionManagerConstPtr question_manager );
	virtual ~ConsoleQuestion( );

public:
	virtual void update( ) = 0;
	virtual void draw( int x, int y ) const = 0;

protected:
	QuestionManagerConstPtr  _question_manager;
};

