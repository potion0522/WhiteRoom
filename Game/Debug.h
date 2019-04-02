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
	void clearSaveMessage( ); // �ۑ��������b�Z�[�W������
	void addSaveMessage( const char* message ); // �ۑ���������
	void addMessage( const char* message ); // ���t���[���X�V

private:
	static Debug* _instance;
	ImplPtr _impl;
};

