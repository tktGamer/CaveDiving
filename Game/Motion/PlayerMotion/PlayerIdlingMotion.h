/**
 * @file   PlayerIdlingMotion.h
 *
 * @brief  プレイヤーの待機モーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/31
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
// クラスの宣言 ===============================================================
class Hand;
// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの待機のモーション
  */
class PlayerIdlingMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
private:
	//手のモーションのY軸座標
	static constexpr float MOTION_Y_POS_MIN = -0.06f;
	static constexpr float MOTION_Y_POS_MAX = 0.1f;
public:

// データメンバの宣言 -----------------------------------------------
private:
	//右手のポインタ
	Hand* m_pRightHand;  

	//左手のポインタ
	Hand* m_pLeftHand;  
	//モーション方向 + -
	int m_operate = 1;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PlayerIdlingMotion(Hand* pRightHand, Hand* pLeftHand);

	// デストラクタ
	~PlayerIdlingMotion();


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

