#pragma once
#include <functional>

class PageContent {
public:
	PageContent( const int& x, const int& y );
	~PageContent( );

public:
	virtual void update( ) = 0;
	virtual void draw( ) const = 0;
	void setCallback( std::function< void( ) > func );

protected:
	const int& _x;
	const int& _y;
	std::function< void( ) > _func;
};

