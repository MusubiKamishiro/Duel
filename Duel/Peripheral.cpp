#include "Peripheral.h"
#include <DxLib.h>
#include <assert.h>


Peripheral::Peripheral()
{
	oldKeyState.fill(0);
	keyState.fill(0);
	oldPadState.fill(0);
	padState.fill(0);
	inputTable.resize(2);
}


Peripheral::~Peripheral()
{
}

void Peripheral::Update()
{
	// �L�[�{�[�h�̍X�V
	oldKeyState = keyState;
	DxLib::GetHitKeyStateAll(keyState.data());
	// �p�b�h�̍X�V
	for (int i = 0; i < DxLib::GetJoypadNum(); ++i)
	{
		oldPadState[i] = padState[i];
		padState[i] = DxLib::GetJoypadInputState(DX_INPUT_PAD1 + i);
	}
}

bool Peripheral::IsPressing(int pno, const char* cmd) const
{
	auto it = inputTable[pno].find(cmd);
	if (it == inputTable[pno].end())
	{
		// �e�[�u���ɑΏۂ̃R�}���h���Ȃ��Ȃ�X�L�b�v
		return false;
	}

	for (int i = 0; i < inputTable[pno].count(cmd); ++i)
	{
		// �L�[�{�[�h�������ꍇ
		if (it->second.padNo == 0)
		{
			if (keyState[it->second.code])
			{
				return keyState[it->second.code];
			}
		}
		else
		{
			// �p�b�h�̏ꍇ
			return (padState[pno] & it->second.code);
		}
		++it;
	}
	return false;
}

bool Peripheral::IsTrigger(int pno, const char* cmd) const
{
	auto it = inputTable[pno].find(cmd);
	if (it == inputTable[pno].end())
	{
		// �e�[�u���ɑΏۂ̃R�}���h���Ȃ��Ȃ�X�L�b�v
		return false;
	}

	for (int i = 0; i < inputTable[pno].count(cmd); ++i)
	{
		// �L�[�{�[�h�������ꍇ
		if (it->second.padNo == 0)
		{
			if (keyState[it->second.code])
			{
				return (!(oldKeyState[it->second.code]) && keyState[it->second.code]);
			}
		}
		else
		{
			// �p�b�h�̏ꍇ
			return (!(oldPadState[pno] & it->second.code) && (padState[pno] & it->second.code));
		}

		++it;
	}
	return false;
}

void Peripheral::AddCommand(unsigned short pno, const char* cmd, int padNo, unsigned int code)
{
	assert(pno < inputTable.size());
	inputTable[pno].emplace(cmd, PeripheralInfo(padNo, code));
}


