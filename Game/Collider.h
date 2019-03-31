#pragma once
#include "smart_ptr.h"
#include "Mathematics.h"

#include "define.h"

/*******************************************************

‚Ç‚ÌŒ`‚Ì“–‚½‚è”»’è‚É‚à‹¤’Ê‚µ‚Ä‚¢‚é‚à‚Ì‚ð‚Ü‚Æ‚ß‚½ƒNƒ‰ƒX

********************************************************/

PTR( Collider );

class Collider {
public:
	Collider( const Vector& pos, OBJECT_TAG tag = OBJECT_TAG_NONE );
	virtual ~Collider( );

public:
	const Vector& getPos( ) const;
	OBJECT_TAG getTag( ) const;
	bool isEnabled( ) const;
	void setEnabled( bool enabled );

public:
	virtual void onColliderEnter( ColliderConstPtr collider );

private:
	const Vector& _pos;
	OBJECT_TAG _tag;
	bool _enabled;
};

