/**
 * @file   PlayerSlamAttackMotion.h
 *
 * @brief  プレイヤーの叩きつけ攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../AttackMotion.h"
// クラスの宣言 ===============================================================
class Sound;
class Hand;
class Player;
// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの叩きつけ攻撃のモーション
  */
class PlayerSlamAttackMotion : public AttackMotion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//モーションの攻撃力補正値
	static constexpr float SLAMMED_ATTACK_MOTION_MODIFIER = 1.3f;
	//モーションスピード
	static constexpr float SLAMMED_ATTACK_MOTION_SPEED = 4.0f;

	//右手の位置
	static constexpr DirectX::SimpleMath::Vector3 RIGHT_HAND_POS = { 0.0f,3.5f,0.0f };
	//左手の位置
	static constexpr DirectX::SimpleMath::Vector3 LEFT_HAND_POS  = { -0.01f,3.4f,0.0f };
	//手のモーション開始角度
	static constexpr float HAND_START_MOTION_X_ANGLE = DirectX::XMConvertToRadians(0.0f);
	//手のモーション終了角度
	static constexpr float HAND_END_MOTION_X_ANGLE   = DirectX::XMConvertToRadians(-70.0f);
	//プレイヤーのモーション開始角度
	static constexpr float PLAYER_START_MOTION_X_ANGLE = DirectX::XMConvertToRadians(0.0f);
	//プレイヤーのモーション終了角度
	static constexpr float PLAYER_END_MOTION_X_ANGLE   = DirectX::XMConvertToRadians(-50.0f);

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	PlayerSlamAttackMotion(Player* pPlayer, Hand* pRightHand,Hand* pLeftHand);
	// デストラクタ
	~PlayerSlamAttackMotion();
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
	//プレイヤーのポインタ
	Player* m_pPlayer;
	//右手のポインタ
	Hand* m_pRightHand;
	//左手のポインタ
	Hand* m_pLeftHand;
	//効果音
	std::unique_ptr<Sound> m_sound;
};

