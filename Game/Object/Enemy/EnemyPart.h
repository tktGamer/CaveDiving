/**
 * @file   EnemyPart.h
 *
 * @brief  敵の体の一部に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Object/GameObject.h"
#include"../Character.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 敵の体の一部
  */
class EnemyPart : public GameObject
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

	//無敵状態か
	bool m_isInvincible;
	//攻撃をくらった方向
	DirectX::SimpleMath::Vector3 m_damageDirection;

	//所有者のキャラクター
	Character* m_parentCharacter;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	EnemyPart(Character* root,
		 GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	virtual ~EnemyPart();


// 操作
public:
	//
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

//　取得・設定
public:

	//大元のキャラクターを取得
	Character* GetRootCharacter();
//　内部操作
private:

};

