#pragma once
#include "ConsoleActiveObservable.h"
#include "ConsoleActiveObserver.h"
#include <vector>

/*

コンソールが開かれた・閉じられたを通知するクラス
発行、購読両機能を持っている

*/

class ConsoleObserver : 
	public ConsoleActiveObservable, public ConsoleActiveObserver {
public:
	ConsoleObserver( );
	virtual ~ConsoleObserver( );

public:
	void subscribeOnActive( std::function< void( bool ) > func );
	void onActive( bool active );

private:
	std::vector< std::function< void( bool ) > > _on_active;
};

