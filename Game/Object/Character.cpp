/**
 * @file   Character.cpp
 *
 * @brief  キャラのステータスに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Character.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Character::Character(int hp, int attack, int diffence, Tag::ObjectType type, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:GameObject{type,parent,initialPosition,initialAngle}
	,m_hp{hp}
	,m_currentHp{hp}
	,m_attackPower{attack}
	,m_diffence{diffence}
{
}



/**
 * @brief デストラクタ
 */
Character::~Character()
{

}

void Character::Damage(int attack)
{
	int damage = attack - m_diffence / 2;
	if (damage < 0) 
	{
		damage = 0;
	}
	m_currentHp -= damage;

	if (m_currentHp < 0) 
	{
		m_currentHp = 0;
	}
}

int& Character::GetCurrentHP()
{
	return m_currentHp;
}

void Character::SetMaxHP(int hp)
{
	m_hp = hp;
}


int& Character::GetMaxHP()
{
	return m_hp;
}

void Character::SetAttackPower(int attack)
{
	m_attackPower = attack;
}

int Character::GetAttackPower()
{
	return m_attackPower;
}

void Character::SetDiffence(int diffence)
{
	m_diffence = diffence;
}

int Character::GetDiffence()
{
	return m_diffence;
}



