/**
 * @file   Weapon.h
 *
 * @brief  武器の基底に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../Object/Character.h"
#include"../Object/GameObject.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 武器の基底
  */
class Weapon : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	//武器の所有者
	Character* m_owner;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Weapon(Character* owner,
		Tag::ObjectType type, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Weapon();


// 操作
public:
//　取得・設定
public:
	//所有者の攻撃力を取得
	const int GetOwnerAttackPower() const;
	//所有者の取得
	Character* GetOwner() const;
//　内部操作
private:

};

