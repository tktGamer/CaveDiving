/**
 * @file   HPAutoRecoveryGem.h
 *
 * @brief  宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/08/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Gem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 宝石
  */
class HPAutoRecoveryGem :public Gem
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	//回復間隔タイマー
	float m_recoveryIntervalTimer = 0.0f;
	//回復間隔
	float m_recoveryInterval = 0.0f;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	// 宝石の種類と効果値を指定して初期化
	HPAutoRecoveryGem(int id, std::string type, Type powerUp, int value);
	HPAutoRecoveryGem(GemAbility ability, GemImagePath image);

	// デストラクタ
	~HPAutoRecoveryGem();


//操作
public:
	void Initialize();

	void UniqueEffect();

	void Finalize();
//取得・設定
public:
//内部操作
private:

};

