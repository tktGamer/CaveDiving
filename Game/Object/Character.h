/**
 * @file   Character.h
 *
 * @brief  キャラのステータスに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../Object/GameObject.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief キャラのステータス
  */
class Character : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	//現在の体力
	int m_currentHp;

	//最大体力
	int m_hp;
	//攻撃力
	int m_attackPower;
	//防御力
	int m_diffence;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Character(int hp,int attack, int diffence,
		Tag::ObjectType type, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// デストラクタ
	~Character();


// 操作
public:
	//ダメージ
	void Damage(int damage);
//　取得・設定
public:
	//現在の体力の取得
	int& GetCurrentHP();
	// 体力の設定
	void SetMaxHP(int hp);
	// 体力の取得
	int& GetMaxHP();
	// 攻撃力の設定
	void SetAttackPower(int attack);
	// 攻撃力の取得
	int GetAttackPower();
	// 防御力の設定
	void SetDiffence(int diffence);
	// 防御力の取得
	int GetDiffence();
//　内部操作
private:

};

