#pragma once
#include<array>

// ���Ӌ@��(�L�[�{�[�h&�p�b�h)�̓��͂𐧌�
class Peripheral
{
private:
	std::array<int, 2> padState;		// ���݂̓��͏��
	std::array<int, 2> lastPadState;	// ���O�t���[���̓��͏��

public:
	Peripheral();
	~Peripheral();

	// ���͏��̍X�V(���t���[��)
	void Update();

	// ���݂̉�����Ԃ̌��o
	// @param pno	�v���C���[�ԍ�
	// @param keyid	���ׂ����L�[�ԍ�
	// @pretval true �����Ă�, false �����ĂȂ�
	bool IsPressing(int pno, int keyid)const;

	// ���݂̃g���K�[���(�������u��)�̌��o
	bool IsTrigger(int pno, int keyid)const;
};

