#pragma once
#include <functional>

/*

�R���\�[���̏�Ԃ��ς�������̒ʒm������@�\��񋟂���N���X

*/

class UIActiveObserverComponent {
public:
	virtual void onActive( bool active ) = 0;
};
