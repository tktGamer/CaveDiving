/**
 * @file   GolemPunchMotion.h
 *
 * @brief  ゴーレムの攻撃のモーションに関するヘッダファイル
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
class Sound;
class Golem;
class GolemHand;
// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの攻撃のモーション
  */
class GolemPunchMotion : public AttackMotion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//モーションの攻撃力補正値
	static constexpr float GOLEM_PUNCH_MOTION_MODIFIER = 1.2f;
	//拳の移動量
	static constexpr DirectX::SimpleMath::Vector3 PUNCH_MOVE = { -3.2f,-1.8f,-13.0f };
	//モーションスピード
	static constexpr float PUNCH_MOTION_SPEED = 2.0f;
	//クールタイム
	static constexpr float COOL_TIME = 0.5f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemPunchMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand);
	// デストラクタ
	~GolemPunchMotion();
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
	//ゴーレムのポインタ
	Golem* m_pGolem;
	//右手のポインタ
	GolemHand* m_pRightGolemHand;
	//左手のポインタ
	GolemHand* m_pLeftGolemHand;
	//パンチのスタート位置
	DirectX::SimpleMath::Vector3 m_startPosition;
	//パンチの目標位置
	DirectX::SimpleMath::Vector3 m_goalPosition;
	//攻撃後の隙の時間
	float m_coolTime = 0.0f;
	//攻撃音
	std::unique_ptr<Sound> m_attackSound;
};

