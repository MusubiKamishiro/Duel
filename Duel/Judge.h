#pragma once
#include <memory>
#include <string>

class TrimString;

// ����񂯂�̌���
enum class Result
{
	DRAW,
	PLAYER1WIN,
	PLAYER2WIN,
	MAX
};


class Judge
{
private:
	Result _result;

	std::unique_ptr<TrimString> _trimString;

public:
	Judge();
	~Judge();

	// �������ʂ𔻒f����
	//@param rSkill...�E�v���C���[�̃X�L��
	//@param lSkill...���v���C���[�̃X�L��
	void JudgeResult(const int& rSkill, const int& lSkill);

	void Draw();

	// �������ʂ��擾����
	Result GetResult()const;
};
