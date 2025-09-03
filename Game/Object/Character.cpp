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
 * @param[in] hp 体力
 * @param[in] attack　攻撃力
 * @param[in] deffence　防御力
 * @param[in] type　オブジェクトの種類
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
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

/**
 * @brief ダメージ処理
 *
 * @param[in] damage 受けるダメージの値
 *
 * @return なし
 */
void Character::Damage(const int damage)
{
	//もしマイナスなら処理を飛ばす
	if (damage < 0) 
	{
		return;
	}

	m_currentHp -= damage;

	if (m_currentHp < 0) 
	{
		m_currentHp = 0;
	}
}

/**
 * @brief 現在のHPを取得
 *
 * @param[in] なし
 *
 * @return 現在のHP
 */
const int& Character::GetCurrentHP()
{
	return m_currentHp;
}

/**
 * @brief 最大HPを設定
 *
 * @param[in] hp 最大HP
 *
 * @return なし
 */
void Character::SetMaxHP(const int hp)
{
	m_hp = hp;
}


/**
 * @brief 最大HPの取得
 *
 * @param[in] なし
 *
 * @return 最大HP
 */
const int& Character::GetMaxHP()
{
	return m_hp;
}

/**
 * @brief 攻撃力の設定
 *
 * @param[in] attack 攻撃力
 *
 * @return なし
 */
void Character::SetAttackPower(const int attack)
{
	m_attackPower = attack;
}

/**
 * @brief 攻撃力の取得
 *
 * @param[in] なし
 *
 * @return 攻撃力
 */
const int Character::GetAttackPower()
{
	return m_attackPower;
}

/**
 * @brief 防御力の設定
 *
 * @param[in] diffence 防御力
 *
 * @return なし
 */
void Character::SetDiffence(const int diffence)
{
	m_diffence = diffence;
}

/**
 * @brief 防御力の取得
 *
 * @param[in] なし
 *
 * @return 防御力
 */
const int Character::GetDiffence()
{
	return m_diffence;
}

/**
 * @brief 死んでいるか
 *
 * @param[in] なし
 *
 * @return true　生きている
 * @return false 死んでいる
 */
bool Character::IsAlive() const
{
	return (m_currentHp > 0);
}


