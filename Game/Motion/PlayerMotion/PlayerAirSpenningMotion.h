/**
 * @file   PlayerAirSpenningMotion.h
 *
 * @brief  プレイヤーの空中回転攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　　2025/12/30
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../AttackMotion.h"
// クラスの宣言 ===============================================================
class Player;
class Hand;
// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの空中回転攻撃のモーション
  */
class PlayerAirSpenningMotion : public AttackMotion
{
// クラス定数の宣言 -------------------------------------------------
private:
	//モーションの攻撃力補正値
	static constexpr float AIR_SPIN_MOTION_MODIFIER = 2.0f;

	//右手の位置
	static constexpr DirectX::SimpleMath::Vector3 RIGHT_HAND_POS = { -1.5f,2.0f,0.0f };
	//左手の位置
	static constexpr DirectX::SimpleMath::Vector3 LEFT_HAND_POS  = { 1.45f,2.0f,0.0f };
	//モーションスピード
	static constexpr float AIR_SPIN_MOTION_SPEED = 5.0f;

	//つるはしの角度
	static constexpr float PIKEL_Z_ANGLE = DirectX::XMConvertToRadians(50.0f);
	//手のモーション開始角度
	static constexpr float HAND_START_MOTION_X_ANGLE = DirectX::XMConvertToRadians(0.0f);
	//手のモーション終了角度
	static constexpr float HAND_END_MOTION_X_ANGLE = DirectX::XMConvertToRadians(-110.0f);
	//プレイヤーのモーション開始角度
	static constexpr float PLAYER_START_MOTION_X_ANGLE = DirectX::XMConvertToRadians(0.0f);
	//プレイヤーのモーション終了角度
	static constexpr float PLAYER_END_MOTION_X_ANGLE = DirectX::XMConvertToRadians(-360.0f);

public:

// データメンバの宣言 -----------------------------------------------
private:
	//プレイヤーのポインタ
	Player * m_pPlayer;
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
	PlayerAirSpenningMotion(Player* pPlayer, Hand* pRightHand, Hand* pLeftHand);

	// デストラクタ
	~PlayerAirSpenningMotion();


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

