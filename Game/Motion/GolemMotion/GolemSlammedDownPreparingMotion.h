/**
 * @file   GolemSlammedDownPreparingMotion.h
 *
 * @brief  ゴーレムの叩きつけ攻撃の準備のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/02
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
// クラスの宣言 ===============================================================
class Golem;
class GolemHand;
class GolemArm;
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
	//腕の移動量
	static constexpr DirectX::SimpleMath::Vector3 SLAM_PREPARE_MOVE = { -1.0f,2.0f,-1.0f };

	//モーション開始角度
	static constexpr float ARM_START_MOTION_X_ANGLE = DirectX::XMConvertToRadians(0.0f);
	//モーション終了角度
	static constexpr float ARM_END_MOTION_X_ANGLE = DirectX::XMConvertToRadians(140.0f);

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemSlammedDownPreparingMotion(const int& golemObjectID);
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
	//右腕のポインタ
	GolemArm* m_pRightGolemArm;
	//右手のポインタ
	GolemHand* m_pRightGolemHand;
	//左腕のポインタ
	GolemArm* m_pLeftGolemArm;
	//左手のポインタ
	GolemHand* m_pLeftGolemHand;
	//拳の始まりの位置
	DirectX::SimpleMath::Vector3 m_handStartPosition;
	//拳の終わりの位置
	DirectX::SimpleMath::Vector3 m_handGoalPosition;
	//攻撃音
	std::unique_ptr<Sound> m_attackSound;
};