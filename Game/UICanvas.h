#pragma once
class UICanvas {
public:
	virtual void update( ) = 0;
	virtual void draw( ) const = 0;
	virtual void close( ) = 0;
	virtual void open( ) = 0;
};

