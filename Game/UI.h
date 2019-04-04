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
	void drawOnClose( ) const;
	void drawOnOpen( ) const;
	void updateIdleTime( );
	void checkOpen( );
	void changeState( UI_STATE state );
	bool isKeyDown( const std::string& key ) const;

private:
	const char* CONSOLE_ACTIVE_KEY = "E";
	const char* HINT_ACTIVE_KEY    = "R";
	const int SHOW_UI_TEXT_START_TIME = 1500;
	const int SHOW_UI_TEXT_ANIM_TIME = 3000;

private:
	int _past_time;
	int _idle_time;
	int _ui_text_alpha;
	std::string _active_key;
	UI_STATE _state;
	UIActiveObserverPtr _observer;
	UICanvasWeakPtr _canvas;
	ConsolePtr _console;
	HintPtr _hint;
	QuestionManagerConstPtr _question_manager;
};

