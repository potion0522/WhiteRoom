#pragma once
#include <functional>

/*

�R���\�[���̏�Ԃ��ς�������̒ʒm������@�\��񋟂���N���X

*/

class ConsoleActiveObserver {
public:
	virtual void onActive( bool active ) = 0;
};
