#pragma once
#include <functional>

/********************************************************

�y�[�W���(�{�^���E���)�̋��ʕ������܂Ƃ߂��N���X

********************************************************/

class PageContent {
public:
	PageContent( const int& x, const int& y, std::function< void( ) > callback );
	~PageContent( );

public:
	virtual void update( ) = 0;
	virtual void draw( ) const = 0;

protected:
	const int& _x;
	const int& _y;
	std::function< void( ) > _callback;
};

