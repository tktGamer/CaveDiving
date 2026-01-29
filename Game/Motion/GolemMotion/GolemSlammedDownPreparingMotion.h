/**
 * @file   GolemSlammedDownPreparingMotion.h
 *
 * @brief  ゴーレムの叩きつけ攻撃の準備のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
// クラスの宣言 ===============================================================
class Golem;
class GolemHand;
// クラスの定義 ===============================================================
/**
  * @brief の攻撃準備のモーション
  */
class GolemSlammedDownPreparingMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	static constexpr DirectX::SimpleMath::Vector3 SLAM_PREPARE_MOVE = { -1.0f,5.0f,-6.0f };
	//拳を正面に向ける
	static constexpr float SLAM_HAND_ANGLE = DirectX::XMConvertToRadians(90.0f);
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemSlammedDownPreparingMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand);
	// デストラクタ
	~GolemSlammedDownPreparingMotion();
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
	//ゴーレム本体のポインタ
	Golem* m_pGolem;
	//右手のポインタ
	GolemHand* m_pRightGolemHand;
	//左手のポインタ
	GolemHand* m_pLeftGolemHand;
	//拳の始まりの位置
	DirectX::SimpleMath::Vector3 m_handStartPosition;
	//拳の終わりの位置
	DirectX::SimpleMath::Vector3 m_handGoalPosition;
	//攻撃音
	std::unique_ptr<Sound> m_attackSound;
};