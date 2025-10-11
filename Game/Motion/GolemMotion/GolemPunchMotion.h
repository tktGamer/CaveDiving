/**
 * @file   GolemPunchMotion.h
 *
 * @brief  の攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
#include"Game/Object/Enemy/Golem/Golem.h"
#include"Game/Object/Enemy/Golem/GolemHand.h"

// クラスの宣言 ===============================================================
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief 攻撃のモーション
  */
class GolemPunchMotion : public Motion
{
	// クラス定数の宣言 -------------------------------------------------
public:


	// データメンバの宣言 -----------------------------------------------
private:
	//のポインタ
	Golem* m_pGolem;
	//右手のポインタ
	GolemHand* m_pRightGolemHand;
	//左手のポインタ
	GolemHand* m_pLeftGolemHand;

	DirectX::SimpleMath::Vector3 m_startPosition;
	DirectX::SimpleMath::Vector3 m_goalPosition;

	//攻撃後の隙の時間
	float m_coolTime;
	std::unique_ptr<Sound> m_attackSound;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemPunchMotion(Golem* pGolem, GolemHand* pRightGolemHand, GolemHand* pLeftGolemHand);

	// デストラクタ
	~GolemPunchMotion();


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

