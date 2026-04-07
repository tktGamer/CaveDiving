/**
 * @file   HPAutoRecoveryGem.h
 *
 * @brief  HP自動回復宝石に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2025/01/04
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Gem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief HP自動回復宝石
  */
class HPAutoRecoveryGem :public Gem
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//回復なし
	static constexpr int NO_HEAL = 0;
	//タイマーリセット
	static constexpr float RESET = 0.0f;

// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	HPAutoRecoveryGem(const GemAbility& ability, const GemImagePath& image);
	//コピー用
	HPAutoRecoveryGem(const HPAutoRecoveryGem& other) = default;
	// デストラクタ
	~HPAutoRecoveryGem();
//操作
	//多態コピー
	std::unique_ptr<Gem> Clone()const override;
	//初期化
	void Initialize();
	//毎フレーム効果
	void OnUpdate(Character& owner) override;

	//HP回復
	int RecoveryHP();
	//終了
	void Finalize();
//内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//回復間隔タイマー
	float m_recoveryIntervalTimer = 0.0f;
};