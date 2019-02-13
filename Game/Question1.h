#pragma once
#include "PageContent.h"
#include "smart_ptr.h"

PTR( Question1 );

class Question1 : public PageContent {
public:
	Question1( const int& x, const int& y, std::function< void( ) > func );
	virtual ~Question1( );

public:
	void update( );
	void draw( ) const;
};

