#pragma once

/************************************************************

�V�[���̃C���^�[�t�F�[�X

************************************************************/

class Scene {
public:
	virtual void update( ) = 0;
	virtual void draw( ) const = 0;
};