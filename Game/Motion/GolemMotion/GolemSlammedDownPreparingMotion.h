/**
 * @file   GolemSlammedDownPreparingMotion.h
 *
 * @brief  ゴーレムの叩きつけ攻撃の準備のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/30
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
private:
	static constexpr DirectX::SimpleMath::Vector3 SLAM_PREPARE_MOVE = { 0.0f,5.0f,-6.0f };
	//拳を正面に向ける
	static constexpr float SLAM_HAND_ANGLE = DirectX::XMConvertToRadians(90.0f);

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

	std::unique_ptr<Sound> m_attackSound;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemSlammedDownPreparingMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand);

	// デストラクタ
	~GolemSlammedDownPreparingMotion();


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

