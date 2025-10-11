/**
 * @file   GolemPunchPreparingMotion.h
 *
 * @brief  コウモリの攻撃準備のモーションに関するヘッダファイル
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
  * @brief コウモリの攻撃準備のモーション
  */
class GolemPunchPreparingMotion : public Motion
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

	DirectX::SimpleMath::Vector3 m_startPosition;
	DirectX::SimpleMath::Vector3 m_goalPosition;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemPunchPreparingMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand);

		// デストラクタ
		~GolemPunchPreparingMotion();


// 操作
public:
	void Initialize();

	bool Update();


	void Reset();

//　取得・設定
public:
	void SetIsNextAttack(bool isNext);
//　内部操作
private:

};

