/**
 * @file   Character.h
 *
 * @brief  キャラクターに関するヘッダファイル
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
  * @brief キャラクター
  */
class Character : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:
	struct  MOVE
	{
		//前
		static constexpr DirectX::SimpleMath::Vector3 FRONT = { 0.0f,0.0f,-1.0f };
		//後ろ
		static constexpr DirectX::SimpleMath::Vector3 BACK  = { 0.0f,0.0f, 1.0f };
		//左
		static constexpr DirectX::SimpleMath::Vector3 LEFT  = {-1.0f,0.0f, 0.0f };
		//右
		static constexpr DirectX::SimpleMath::Vector3 RIGHT = { 1.0f,0.0f, 0.0f };
		//左前
		static constexpr DirectX::SimpleMath::Vector3 LEFT_FRONT  = { -1.0f,0.0f,-1.0f };
		//右前
		static constexpr DirectX::SimpleMath::Vector3 RIGHT_FRONT = { 1.0f,0.0f,-1.0f };
		//左後ろ
		static constexpr DirectX::SimpleMath::Vector3 LEFT_BACK   = { -1.0f,0.0f, 1.0f };
		//右後ろ
		static constexpr DirectX::SimpleMath::Vector3 RIGHT_BACK  = { 1.0f,0.0f, 1.0f };

	};

	static constexpr float NO_DAMAGE_FLASH = 0.0f;

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

	//ダメージフラッシュ ダメージを受けたとき1.0をセット
	float m_damageFlash;

	//無敵状態か
	bool m_isInvincible;
	//攻撃をくらった方向
	DirectX::SimpleMath::Vector3 m_damageDirection;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Character(int hp,int attack, int diffence,
		Tag::ObjectType type, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	virtual ~Character();


// 操作
public:
	//ダメージを受けたときの処理
	virtual void OnDamage(GameObject* other);

	//ダメージを受ける
	void TakeDamage(const int& damage);

	//ダメージフラッシュ更新
	void DamageFlashUpdate();
//　取得・設定
public:
	//現在の体力の取得
	const int& GetCurrentHP();
	//現在の体力の設定
	virtual void SetCurrentHP();
	// 体力の設定
	void SetMaxHP(const int& hp);
	// 体力の取得
	virtual const int GetMaxHP();
	// 攻撃力の設定
	void SetAttackPower(const int& attack);
	// 攻撃力の取得
	virtual const int GetAttackPower();
	// 防御力の設定
	void SetDiffence(const int& diffence);
	// 防御力の取得
	virtual const int GetDiffence();

	//生きているか
	bool IsAlive() const;

	//ダメージを受けた方向の取得
	const DirectX::SimpleMath::Vector3& GetDamageDirection() const;

	void SetDamageDirection(const DirectX::SimpleMath::Vector3& damageDirection);
	//無敵か
	const bool IsInvincible() const;

	//無敵の設定
	void SetInvincible(const bool& isInvinccible);

	//ダメージフラッシュ
	void SetDamageFlash(const float& flash = 1.0f);
	const float& GetDamageFlash() const;

//　内部操作
private:

};

