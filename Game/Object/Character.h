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
	struct  MOVE
	{
		static constexpr DirectX::SimpleMath::Vector3 FRONT = { 0.0f,0.0f,-1.0f };
		static constexpr DirectX::SimpleMath::Vector3 BACK  = { 0.0f,0.0f, 1.0f };
		static constexpr DirectX::SimpleMath::Vector3 LEFT  = {-1.0f,0.0f, 0.0f };
		static constexpr DirectX::SimpleMath::Vector3 RIGHT = { 1.0f,0.0f, 0.0f };

	};

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
	virtual ~Character();


// 操作
public:
	//ダメージ
	void Damage(const int damage);
//　取得・設定
public:
	//現在の体力の取得
	const int& GetCurrentHP();
	//現在の体力の設定
	virtual void SetCurrentHP();
	// 体力の設定
	void SetMaxHP(const int hp);
	// 体力の取得
	virtual const int GetMaxHP();
	// 攻撃力の設定
	void SetAttackPower(const int attack);
	// 攻撃力の取得
	virtual const int GetAttackPower();
	// 防御力の設定
	void SetDiffence(const int diffence);
	// 防御力の取得
	virtual const int GetDiffence();

	//生きているか
	bool IsAlive() const;

//　内部操作
private:

};

