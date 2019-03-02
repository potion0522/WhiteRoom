#pragma once
#include "ConsoleActiveObservable.h"
#include "ConsoleActiveObserver.h"
#include <vector>

/*

�R���\�[�����J���ꂽ�E����ꂽ��ʒm����N���X
���s�A�w�Ǘ��@�\�������Ă���

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

