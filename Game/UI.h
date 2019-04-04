#pragma once
#include "smart_ptr.h"
#include <string>

PTR( UI );
PTR( ElevatorButton );
PTR( QuestionManager );
PTR( UICanvas );
PTR( Console );
PTR( Hint );
PTR( UIActiveObserver );
PTR( UIActiveObservableComponent );

class UI {
private:
	enum UI_STATE {
		UI_STATE_CLOSE,
		UI_STATE_OPEN
	};

public:
	UI( ElevatorButtonPtr, QuestionManagerPtr );
	virtual ~UI( );

public:
	void update( );
	void draw( ) const;
	UIActiveObservableComponentPtr getActiveObservable( ) const;

private:
	void actOnClose( );
	void actOnOpen( );
	bool isKeyDown( const std::string& key ) const;

private:
	const char* CONSOLE_ACTIVE_KEY = "E";
	const char* HINT_ACTIVE_KEY    = "R";

private:
	std::string _active_key;
	UI_STATE _state;
	UIActiveObserverPtr _observer;
	UICanvasWeakPtr _canvas;
	ConsolePtr _console;
	HintPtr _hint;
};

