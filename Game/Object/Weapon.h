/**
 * @file   Weapon.h
 *
 * @brief  武器の基底に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/25
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Object/GameObject3D.h"
// クラスの宣言 ===============================================================
class Character;
// クラスの定義 ===============================================================
/**
  * @brief 武器の基底
  */
class Weapon : public GameObject3D
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//所有者の攻撃力を取得
	const int GetOwnerAttackPower() const;
	//所有者の取得
	Character* GetOwner() const;
// コンストラクタ/デストラクタ
	// コンストラクタ
	Weapon(Character* owner, const Tag::ObjectType& type,const GameObject3D* parent, const Transform& transform);
	// デストラクタ
	~Weapon();
// 操作

//　内部操作
private:
// データメンバの宣言 -----------------------------------------------
private:
	//武器の所有者
	Character* m_owner;
};