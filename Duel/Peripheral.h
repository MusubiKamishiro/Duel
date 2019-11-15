#pragma once
#include <vector>
#include <array>
#include <map>
#include <string>

// ���͏��
struct PeripheralInfo
{
	PeripheralInfo() {};
	PeripheralInfo(int no, int c) : padNo(no), code(c) {};

	unsigned int padNo = 0;	// �p�b�h�ԍ�	//@details 0...�L�[�{�[�h 1~4...�p�b�h
	unsigned int code = 0;	// ���̓R�[�h
};

// ���Ӌ@��(�L�[�{�[�h&�p�b�h)�̓��͂𐧌�
class Peripheral
{
private:
	std::array<char, 256> keyState;		// �L�[�{�[�h�̓��͏��
	std::array<char, 256> oldKeyState;
	std::array<int, 2> padState;		// �p�b�h�̓��͏��
	std::array<int, 2> oldPadState;

	// ���͑Ή��e�[�u��
	//@param string			�R�}���h������
	//@param PeripheralInfo	���͏��
	std::vector<std::multimap<std::string, PeripheralInfo>> inputTable;

public:
	Peripheral();
	~Peripheral();

	// ���͏��̍X�V(���t���[��)
	void Update();

	// ���݂̉�����Ԃ̌��o
	//@param pno	�v���C���[�ԍ�
	//@param cmd	���ׂ����R�}���h������
	//@retval true	�����Ă�, false �����ĂȂ�
	bool IsPressing(const int& pno, const char* cmd)const;

	// ���݂̃g���K�[���(�������u��)�̌��o
	//@param pno	�v���C���[�ԍ�
	//@param cmd	���ׂ����R�}���h������
	//@retval true	������, false �����ĂȂ�
	bool IsTrigger(const int& pno, const char* cmd)const;

	// �R�}���h�ݒ�
	//@param pno	�v���C���[�ԍ�
	//@param cmd	�R�}���h������
	//@param preiNo	�p�b�h�ԍ�
	//@param code	���̓R�[�h
	void AddCommand(const int& pno, const char* cmd, const unsigned int& padNo, const unsigned int& code);
};

