#include "Peripheral.h"
#include <DxLib.h>


Peripheral::Peripheral()
{
	for (int i = 0; i < padState.size(); ++i)
	{
		lastPadState[i] = 0;
		padState[i] = 0;
	}
}


Peripheral::~Peripheral()
{
}

void Peripheral::Update()
{
	lastPadState = padState;
	padState[0] = DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1);
	padState[1] = DxLib::GetJoypadInputState(DX_INPUT_PAD2);
}

bool Peripheral::IsPressing(int pno, int keyid) const
{
	return (padState[pno] & keyid);
}

bool Peripheral::IsTrigger(int pno, int keyid) const
{
	return (!(lastPadState[pno] & keyid) && (padState[pno] & keyid));
}


