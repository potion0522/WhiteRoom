#pragma once
#include <functional>

/*

コンソールの状態が変わった時の通知をする機能を提供するクラス

*/

class UIActiveObserverComponent {
public:
	virtual void onActive( bool active ) = 0;
};
