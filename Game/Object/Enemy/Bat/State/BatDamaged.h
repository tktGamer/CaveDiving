/**
 * @file   BatDamaged.h
 *
 * @brief  コウモリのダメージをくらった状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_DAMAGED_DEFINED
#define BAT_DAMAGED_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
// クラスの宣言 ===============================================================
class Bat;
class Motion;
// クラスの定義 ===============================================================
/**
  * @brief コウモリのダメージをくらった状態
  */
class BatDamaged : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//ノックバックの力
	static constexpr float KNOCKBACK_POWER = 15.0f;
	//ノックバックの時間
	static constexpr float KNOCKBACK_TIME = 0.5f;
	//遷移までの時間
	static constexpr float CHANGE_IDLING_TIME = 1.5f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
//  コンストラクタ/デストラクタ
	// コンストラクタ
	BatDamaged(Bat* bat);
	// デストラクタ
	~BatDamaged();
//  操作
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
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// コウモリ
	Bat* m_bat;
	//ダメージリアクションモーション
	std::unique_ptr<Motion> m_damageMotion;
};
#endif		// BAT_DAMAGED_DEFINED