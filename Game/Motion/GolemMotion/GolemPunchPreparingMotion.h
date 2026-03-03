/**
 * @file   GolemPunchPreparingMotion.h
 *
 * @brief  ゴーレムのパンチ攻撃準備のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
// クラスの宣言 ===============================================================
class Golem;
class GolemArm;
// クラスの定義 ===============================================================
/**
  * @brief ゴーレムのパンチ攻撃の準備のモーション
  */
class GolemPunchPreparingMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//拳をひく位置
	static constexpr DirectX::SimpleMath::Vector3 HAND_GOAL_POS = { 0.0f,0.5f,6.0f };
	//拳を正面に向ける
	static constexpr float PUNCH_HAND_ANGLE = DirectX::XMConvertToRadians(90.0f);
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemPunchPreparingMotion(const int& golemObjectID);
	// デストラクタ
	~GolemPunchPreparingMotion();
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
	//パンチのスタート位置
	DirectX::SimpleMath::Vector3 m_startPosition;
	DirectX::SimpleMath::Vector3 m_goalPosition;
};

