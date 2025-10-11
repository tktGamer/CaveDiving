/**
 * @file   GolemSlammedDownPreparingMotion.h
 *
 * @brief  の攻撃準備のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/30
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"
// クラスの宣言 ===============================================================
class Golem;
// クラスの定義 ===============================================================
/**
  * @brief の攻撃準備のモーション
  */
class GolemSlammedDownPreparingMotion : public Motion
{
	// クラス定数の宣言 -------------------------------------------------
public:


	// データメンバの宣言 -----------------------------------------------
private:
	//ゴーレム本体のポインタ
	Golem* m_pGolem;
	//右手のポインタ
	GolemHand* m_pRightGolemHand;
	//左手のポインタ
	GolemHand* m_pLeftGolemHand;

	DirectX::SimpleMath::Vector3 m_rightHandStartPosition;
	DirectX::SimpleMath::Vector3 m_rightHandGoalPosition;
	DirectX::SimpleMath::Vector3 m_leftHandStartPosition;
	DirectX::SimpleMath::Vector3 m_leftHandGoalPosition;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemSlammedDownPreparingMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand);

	// デストラクタ
	~GolemSlammedDownPreparingMotion();


// 操作
public:
	void Initialize();

	bool Update();


	void Reset();

//　取得・設定
public:
	
//　内部操作
private:

};

