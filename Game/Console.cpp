#include "Console.h"
#include "ElevatorButton.h"
#include "Page.h"
#include "SoundManager.h"

#include "Image.h"
#include "Keyboard.h"
#include "Drawer.h"
#include "Mouse.h"

const char* CONSOLE_BG_FILEPATH = "Game/UI/UIBG.png";
const double SLIDE_DETECT_LENGTH = SCREEN_HEIGHT * 0.10; // ��ʍ�����10%�ȏ�ŃX���C�h

Console::Console( ElevatorButtonPtr elevator_button, QuestionManagerConstPtr question_manager ) :
_elevator_button( elevator_button ), 
_state( CONSOLE_STATE_IDLE ),
_page_num( _INIT_PAGE_NUM ),
_slide_start_pos( ),
_slide_end_pos( ) {
	MousePtr mouse = Mouse::getTask( );
	mouse->setMouseDraw( false );

	// �w�i
	DrawerPtr drawer = Drawer::getTask( );
	_bg = drawer->getImage( CONSOLE_BG_FILEPATH );

	for ( int i = 0; i < MAX_PAGE_NUM; i++ ) {
		_pages[ i ] = PagePtr( new Page( ( PAGE_NUM )i, [ & ]( const FLOOR floor ) { orderFloorChangeToElevator( floor ); }, question_manager ) );
	}

	// �y�[�W���W��������
	slidePage( 0, -CONSOLE_HEIGHT * _INIT_PAGE_NUM );
}

Console::~Console( ) {
	MousePtr mouse = Mouse::getTask( );
	mouse->setMouseDraw( true );
}

void Console::update( ) {
	switch ( _state ) {
		case CONSOLE_STATE_IDLE:
			actOnIdle( );
			break;
		case CONSOLE_STATE_SLIDE_UP:
			actOnSlideUp( );
			break;
		case CONSOLE_STATE_SLIDE_DOWN:
			actOnSlideDown( );
			break;
		case CONSOLE_STATE_SLIDE_LEFT:
			actOnSlideLeft( );
			break;
		case CONSOLE_STATE_SLIDE_RIGHT:
			actOnSlideRight( );
			break;
	}
}

void Console::draw( ) const {
	_bg->draw( );

	for ( int i = 0; i < MAX_PAGE_NUM; i++ ) {
		_pages[ i ]->draw( );
	}
}


void Console::close( ) {
	_pages[ _page_num ]->refreshExceptForAnswer( );
}

void Console::open( ) {
	changeState( CONSOLE_STATE_IDLE );
}


bool Console::isChangeActivate( ) const {
	return Keyboard::getTask( )->getKeyDown( "E" );
}

void Console::changeState( CONSOLE_STATE state ) {
	_state = state;
}

void Console::slidePage( int add_x, int add_y ) {
	for ( int i = 0; i < MAX_PAGE_NUM; i++ ) {
		_pages[ i ]->slide( add_x, add_y );
	}
}

void Console::actOnIdle( ) {
	_pages[ _page_num ]->update( );

	// �X���C�h�����m
	MousePtr mouse = Mouse::getTask( );

	// �N���b�N������
	if ( mouse->isClickDownLeft( ) ) {
		_slide_start_pos = mouse->getPoint( );
	}

	// �N���b�N���I���
	if ( mouse->isClickUpLeft( ) ) {
		_slide_end_pos = mouse->getPoint( );


		// �X���C�h����
		Vector slide = _slide_end_pos - _slide_start_pos;
		if ( slide.getLength2( ) < SLIDE_DETECT_LENGTH * SLIDE_DETECT_LENGTH ) {
			return;
		}

		// �X���C�h����
		bool horizontal = fabs( slide.x ) > fabs( slide.y );

		// ������E�ɃX���C�h
		if ( horizontal && slide.x > 0 && _page_num == PAGE_NUM_6 ) {
			changeState( CONSOLE_STATE_SLIDE_RIGHT );
			SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_SLIDE );
		} 
		// �E���獶�ɃX���C�h
		if ( horizontal && slide.x < 0 && _page_num == PAGE_NUM_4 ) {
			changeState( CONSOLE_STATE_SLIDE_LEFT );
			SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_SLIDE );
		} 

		// �ォ�牺�ɃX���C�h
		if ( !horizontal && slide.y > 0 && _page_num != PAGE_NUM_6 && _page_num != PAGE_NUM_1 ) {
			changeState( CONSOLE_STATE_SLIDE_DOWN );
			SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_SLIDE );
		} 
		// �������ɃX���C�h
		if ( !horizontal && slide.y < 0 && _page_num != PAGE_NUM_6 && _page_num != PAGE_NUM_5 ) {
			changeState( CONSOLE_STATE_SLIDE_UP );
			SoundManager::getInstance( )->play( SoundManager::SE_CONSOLE_SLIDE );
		}
	}
}

void Console::actOnSlideUp( ) {
	slidePage( 0, -CONSOLE_HEIGHT );
	changeState( CONSOLE_STATE_IDLE );
	_page_num = ( PAGE_NUM )( ( _page_num + 1 ) % ( MAX_PAGE_NUM - 1 ) );
}

void Console::actOnSlideDown( ) {
	slidePage( 0, CONSOLE_HEIGHT );
	changeState( CONSOLE_STATE_IDLE );
	_page_num = ( PAGE_NUM )( ( _page_num + ( MAX_PAGE_NUM - 1 ) - 1 ) % ( MAX_PAGE_NUM - 1 ) );
}

void Console::actOnSlideLeft( ) {
	slidePage( -CONSOLE_WIDTH, 0 );
	changeState( CONSOLE_STATE_IDLE );
	_page_num = PAGE_NUM_6;
}

void Console::actOnSlideRight( ) {
	slidePage( CONSOLE_WIDTH, 0 );
	changeState( CONSOLE_STATE_IDLE );
	_page_num = PAGE_NUM_4;
}

void Console::orderFloorChangeToElevator( FLOOR floor ) {
	_elevator_button->pushButton( floor );
}