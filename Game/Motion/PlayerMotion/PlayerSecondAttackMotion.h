/**
 * @file   PlayerSecondAttackMotion.h
 *
 * @brief  プレイヤーの第二攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
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
class PlayerSecondAttackMotion : public AttackMotion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//モーションの攻撃力補正値
	static constexpr float SECOND_ATTACK_MOTION_MODIFIER = 1.0f;
	//モーションスピード
	static constexpr float SECOND_ATTACK_MOTION_SPEED = 5.0f;
	//右手のモーション開始角度
	static constexpr float RIGHT_HAND_START_MOTION_Y_ANGLE = DirectX::XMConvertToRadians(170.0f);
	//右手のモーション終了角度
	static constexpr float RIGHT_HAND_END_MOTION_Y_ANGLE   = DirectX::XMConvertToRadians(0.0f);
	//左手のモーション開始角度
	static constexpr float LEFT_HAND_START_MOTION_Y_ANGLE = DirectX::XMConvertToRadians(30.0f);
	//左手のモーション終了角度
	static constexpr float LEFT_HAND_END_MOTION_Y_ANGLE   = DirectX::XMConvertToRadians(-30.0f);

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	PlayerSecondAttackMotion(Hand* pRightHand, Hand* pLeftHand);
	// デストラクタ
	~PlayerSecondAttackMotion();
// 操作
	//初期化
	void Initialize();
	//更新
	bool Update();
	//リセット
	void Reset();
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//右手のポインタ
	Hand* m_pRightHand;
	//左手のポインタ
	Hand* m_pLeftHand;
	//効果音
	std::unique_ptr<Sound> m_sound;
};