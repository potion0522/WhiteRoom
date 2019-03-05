#pragma once
#include <functional>

/********************************************************

�y�[�W���(�{�^���E���)�̋��ʕ������܂Ƃ߂��N���X

********************************************************/

class PageContent {
public:
	PageContent( std::function< void( ) > callback );
	~PageContent( );

public:
	virtual void update( ) = 0;
	virtual void draw( int x, int y ) const = 0;

protected:
	std::function< void( ) > _callback;
};

