#pragma once
#include <functional>

/*

コンソールが開かれたときの処理を登録する機構を提供するクラス

*/

class UIActiveObservableComponent {
public:
	virtual void subscribeOnActive( std::function< void( bool ) > ) = 0;
};