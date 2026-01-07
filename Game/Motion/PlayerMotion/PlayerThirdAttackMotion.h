/**
 * @file   PlayerThirdAttackMotion.h
 *
 * @brief  プレイヤーの第三攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/31
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../AttackMotion.h"
// クラスの宣言 ===============================================================
class Hand;
// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの攻撃のモーション
  */
class PlayerThirdAttackMotion : public AttackMotion
{
// クラス定数の宣言 -------------------------------------------------
private:
	//モーションの攻撃力補正値
	static constexpr float THIRD_ATTACK_MOTION_MODIFIER = 1.5f;

	//モーションスピード
	static constexpr float THIRD_ATTACK_MOTION_SPEED = 4.0f;

	//右手のモーション開始角度
	static constexpr float RIGHT_HAND_START_MOTION_Y_ANGLE = DirectX::XMConvertToRadians(0.0f);
	//右手のモーション終了角度
	static constexpr float RIGHT_HAND_END_MOTION_Y_ANGLE = DirectX::XMConvertToRadians(360.0f);
	//左手のモーション開始角度
	static constexpr float LEFT_HAND_START_MOTION_Y_ANGLE = DirectX::XMConvertToRadians(-177.0f);
	//左手のモーション終了角度
	static constexpr float LEFT_HAND_END_MOTION_Y_ANGLE = DirectX::XMConvertToRadians(190.0f);

public:

// データメンバの宣言 -----------------------------------------------
private:

	//右手のポインタ
	Hand* m_pRightHand;  
	//左手のポインタ
	Hand* m_pLeftHand;  


	//効果音
	std::unique_ptr<Sound> m_sound;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerThirdAttackMotion(Hand* pRightHand, Hand* pLeftHand);

	// デストラクタ
	~PlayerThirdAttackMotion();


// 操作
public:
	//初期化
	void Initialize();
	//更新
	bool Update();

	//リセット
	void Reset();

//　取得・設定
public:

//　内部操作
private:

};

