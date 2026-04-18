/**
 * @file   Weapon.cpp
 *
 * @brief  武器の基底に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/04/09
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Weapon.h"
#include "../Object/Character.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] owner 所有者
 * @param[in] type　オブジェクトの種類
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
Weapon::Weapon(Character* owner, const Tag::ObjectType& type, const GameObject3D* parent, const Transform& transform)
	:
	GameObject3D{type,parent,transform},
	m_owner{owner}
{
}

/**
 * @brief デストラクタ
 */
Weapon::~Weapon()
{
}

/**
 * @brief 所有者の攻撃力を取得する
 *
 * @param[in] なし
 *
 * @return 所有者の攻撃力
 */
const int Weapon::GetOwnerAttackPower() const
{
	return m_owner->GetAttackPower();
}

/**
 * @brief 所有者を取得する
 *
 * @param[in] なし
 *
 * @return 所有者
 */
Character* Weapon::GetOwner() const
{
	return m_owner;
}