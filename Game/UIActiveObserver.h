#pragma once
#include "UIActiveObserverComponent.h"
#include "UIActiveObservableComponent.h"
#include <vector>

/*

�R���\�[�����J���ꂽ�E����ꂽ��ʒm����N���X
���s�A�w�Ǘ��@�\�������Ă���

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

