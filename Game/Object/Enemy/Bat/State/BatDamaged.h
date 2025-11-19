/**
 * @file   BatDamaged.h
 *
 * @brief  コウモリのダメージをくらった状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_DAMAGED_DEFINED
#define BAT_DAMAGED_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"

#include"Game/Motion/BatMotion/BatDamageMotion.h"
// クラスの宣言 ===============================================================
class Bat;

// クラスの定義 ===============================================================
/**
  * @brief コウモリの待機状態
  */
class BatDamaged : public IState
{
private:
	// コウモリ
	Bat* m_bat;
	//ダメージリアクションモーション
	std::unique_ptr<Motion> m_damageMotion;
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	BatDamaged(Bat* bat);
	// デストラクタ
	~BatDamaged();
	// 初期化する
	void Initialize();
	// 事前更新する
	void PreUpdate();
	// 更新する
	void Update(const float& elapsedTime);
	// 事後更新する
	void PostUpdate();
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();

};

#endif		// SOLDIER_IDLING_DEFINED
