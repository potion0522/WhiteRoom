#pragma once
#include <functional>

/*

�R���\�[�����J���ꂽ�Ƃ��̏�����o�^����@�\��񋟂���N���X

*/

class ConsoleActiveObservable {
public:
	virtual void subscribeOnActive( std::function< void( bool ) > ) = 0;
};