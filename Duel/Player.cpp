#include "Player.h"
#include <DxLib.h>
#include <random>
#include "Peripheral.h"
#include "Game.h"

#include "AI.h"

#include "Loader/FileSystem.h"
#include "Loader/ImageLoader.h"
#include "Loader/SoundLoader.h"


Player::Player(const Vector2<int>& pos, const InitStatus& initStatus, const bool& aiFlag)
{
	for (int i = 0; i < static_cast<int>(Skill::MAX); ++i)
	{
		if (initStatus.goodSkill != i)
		{
			_playerData.skillCount[i] = 1;
			_playerData.initSkillCount[i] = 1;
		}
		else
		{
			_playerData.skillCount[i] = 2;
			_playerData.initSkillCount[i] = 2;
		}
	}
	_playerData.img = Game::Instance().GetFileSystem()->Load("img/char" + std::to_string(initStatus.charNum) + ".png");
	_playerData.maxHp = initStatus.maxHp;
	_playerData.hp = _playerData.maxHp;
	_playerData.power = initStatus.power;
	_playerData.skillName = initStatus.skillName;
	_playerData.goodSkill = initStatus.goodSkill;

	_playerData.skill = Skill::MAX;
	_playerData.decideFlag = false;
	_pos = pos;
	_aiFlag = aiFlag;

	_frameImg = Game::Instance().GetFileSystem()->Load("img/frame2.png");
	_decideSound = Game::Instance().GetFileSystem()->Load("sound/se/decide.mp3");
	_damageSound = Game::Instance().GetFileSystem()->Load("sound/se/damage.mp3");

	_swing = Vector2<float>(0, 0);
	_damageFlag = false;
	_damage = 0;

	if (aiFlag)
	{
		_ai.reset(new AI());
	}
}

Player::~Player()
{
}

void Player::Check(const Skill& skill)
{
	if ((_playerData.skillCount[static_cast<int>(skill)] > 0) && (_playerData.decideFlag == false))
	{
		_playerData.skill = skill;
		_playerData.decideFlag = true;

		DxLib::PlaySoundMem(_decideSound, DX_PLAYTYPE_BACK);
	}
}

void Player::DamageUpdate(const int& count)
{
	if (_damageFlag)
	{
		_swing = Vector2<float>(10, 10);
		_damageFlag = false;
	}

	if (count < 30)
	{
		_playerData.hp -= static_cast<float>(_damage) / 30;
	}
	else
	{
		_damage = 0;
	}
	if (_playerData.hp < 0)
	{
		_playerData.hp = 0;
	}
}

void Player::Update(const int& pno, const PlayerData& enemyData, const Peripheral& p)
{
	if (!_playerData.decideFlag)
	{
		if (!_aiFlag)
		{
			if (p.IsTrigger(pno, "ROCK"))
			{
				Check(Skill::ROCK);
			}
			else if (p.IsTrigger(pno, "SCISSORS"))
			{
				Check(Skill::SCISSORS);
			}
			else if (p.IsTrigger(pno, "PAPER"))
			{
				Check(Skill::PAPER);
			}
		}
		else
		{
			_ai->Update(_playerData, enemyData);
			Check(_ai->GetAISkill());
		}
	}
}

void Player::Draw()
{
	if (std::abs(_swing.x) < 0.5f)
	{
		_swing = Vector2<float>(0, 0);
	}
	else
	{
		_swing *= 0.95f;

		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());
		if ((engine() % 4) == 0)
		{
			_swing = Vector2<float>(_swing.x, _swing.y);
		}
		else if ((engine() % 4) == 1)
		{
			_swing = Vector2<float>(-_swing.x, _swing.y);
		}
		else if ((engine() % 4) == 2)
		{
			_swing = Vector2<float>(_swing.x, -_swing.y);
		}
		else if ((engine() % 4) == 3)
		{
			_swing = Vector2<float>(-_swing.x, -_swing.y);
		}
	}

	DxLib::DrawExtendGraph(_pos.x - 450/2 + _swing.x, _pos.y + _swing.y, _pos.x + 450/2 + _swing.x, _pos.y + 600 + _swing.y, _playerData.img, true);
	DxLib::DrawExtendGraph(_pos.x - 500/2 + _swing.x, _pos.y - 50 + _swing.y, _pos.x + 500/2 + _swing.x, _pos.y + 620 + _swing.y, _frameImg, true);
}

void Player::Damage(const int& power)
{
	DxLib::PlaySoundMem(_damageSound, DX_PLAYTYPE_BACK);

	_damageFlag = true;
	_damage += power;
}

const int& Player::GetPower() const
{
	return _playerData.power[static_cast<int>(_playerData.skill)];
}

const PlayerData& Player::GetPlayerData() const
{
	return _playerData;
}

const Vector2<int>& Player::GetPos() const
{
	return _pos;
}

void Player::SetSkill()
{
	_playerData.decideFlag = false;
	--_playerData.skillCount[static_cast<int>(_playerData.skill)];
	_playerData.skill = Skill::MAX;
}

void Player::ResetCount()
{
	_playerData.skillCount = _playerData.initSkillCount;
}
