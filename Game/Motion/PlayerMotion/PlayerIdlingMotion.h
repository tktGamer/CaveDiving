/**
 * @file   PlayerIdlingMotion.h
 *
 * @brief  プレイヤーの待機モーションに関するヘッダファイル
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
class Hand;
// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの待機のモーション
  */
class PlayerIdlingMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//手のモーションのY軸座標
	static constexpr float MOTION_Y_POS_MIN = -0.06f;
	static constexpr float MOTION_Y_POS_MAX = 0.1f;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	PlayerIdlingMotion(Hand* pRightHand, Hand* pLeftHand);
	// デストラクタ
	~PlayerIdlingMotion();
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
	//右手のポインタ
	Hand* m_pRightHand;
	//左手のポインタ
	Hand* m_pLeftHand;
	//モーション方向 + -
	int m_operate;
};

