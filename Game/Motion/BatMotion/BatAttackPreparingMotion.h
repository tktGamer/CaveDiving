/**
 * @file   BatAttackPreparingMotion.h
 *
 * @brief  コウモリの攻撃準備のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
#include"Game/Object/Enemy/Bat/Wing.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃準備のモーション
  */
class BatAttackPreparingMotion : public Motion
{
	// クラス定数の宣言 -------------------------------------------------
public:


	// データメンバの宣言 -----------------------------------------------
private:
	//右手のポインタ
	Wing* m_pRightWing; 
	//左手のポインタ
	Wing* m_pLeftWing;  

	int m_numLoop;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
	public:
		// コンストラクタ
		BatAttackPreparingMotion(Wing* pRightWing,Wing* pLeftWing);

		// デストラクタ
		~BatAttackPreparingMotion();


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

