#pragma once
#include <functional>

/********************************************************

ページ情報(ボタン・問題)の共通部分をまとめたクラス

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

