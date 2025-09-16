/**
 * @file   Weapon.cpp
 *
 * @brief  キャラのステータスに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Weapon.h"

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
Weapon::Weapon(Character* owner, Tag::ObjectType type, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{type,parent,initialPosition,initialAngle}
	,m_owner{owner}
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



