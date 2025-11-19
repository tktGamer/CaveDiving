/**
 * @file   BatAttackMotion.h
 *
 * @brief  コウモリの攻撃のモーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/05
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion.h"
#include"Game/Object/Enemy/Bat/Bat.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃のモーション
  */
class BatAttackMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	//コウモリのポインタ
	Bat* m_pBat;
	//右手のポインタ
	Wing* m_pRightWing;
	//左手のポインタ
	Wing* m_pLeftWing;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	BatAttackMotion(Bat* pBat, Wing* pRightWing, Wing* pLeftWing);

	// デストラクタ
	~BatAttackMotion();


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

