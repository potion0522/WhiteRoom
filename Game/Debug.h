#pragma once
#include "smart_ptr.h"
#include <string>

PTR( Impl );

class Debug {
private:
	Debug( );
	virtual ~Debug( );

public:
	static Debug* getInstance( );

public:
	void finalize( );
	void update( );

public:
	void clearSaveMessage( ); // 保存したメッセージを消す
	void addSaveMessage( const char* message ); // 保存し続ける
	void addMessage( const char* message ); // 毎フレーム更新

private:
	static Debug* _instance;
	ImplPtr _impl;
};

