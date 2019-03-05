#pragma once
#include <functional>

/********************************************************

ページ情報(ボタン・問題)の共通部分をまとめたクラス

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

