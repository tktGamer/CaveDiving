/**
 * @file   BatChasing.h
 *
 * @brief  コウモリの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/09/03
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_CHASING_DEFINED
#define BAT_CHASING_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
// クラスの宣言 ===============================================================
class Bat;
class GameObject;
// クラスの定義 ===============================================================
/**
  * @brief コウモリの追跡状態
  */
class BatChasing : public IState
{
	// クラス定数の宣言 -------------------------------------------------
public:
private:
	// コウモリ
	Bat* m_bat;

	const GameObject* m_pPlayer;
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	BatChasing(Bat* bat);
	// デストラクタ
	~BatChasing();
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
//内部処理
private:
	//二点のラジアン角を求める
	const float CaluculateRadian(const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& target);
};
#endif		// BAT_IDLING_DEFINED
