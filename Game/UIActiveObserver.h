#pragma once
#include "UIActiveObserverComponent.h"
#include "UIActiveObservableComponent.h"
#include <vector>

/*

コンソールが開かれた・閉じられたを通知するクラス
発行、購読両機能を持っている

*/

class UIActiveObserver : 
	public UIActiveObserverComponent, public UIActiveObservableComponent {
public:
	UIActiveObserver( );
	virtual ~UIActiveObserver( );

public:
	void subscribeOnActive( std::function< void( bool ) > func );
	void onActive( bool active );

private:
	std::vector< std::function< void( bool ) > > _on_active;
};

