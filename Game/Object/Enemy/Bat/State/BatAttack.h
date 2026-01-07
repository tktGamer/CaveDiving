/**
 * @file   BatAttack.h
 *
 * @brief  コウモリの移動状態に関するヘッダファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/12/31
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef BAT_ATTACK_DEFINED
#define BAT_ATTACK_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Interface/IState.h"

#include"Game/Motion/BatMotion/BatAttackMotion.h"
// クラスの宣言 ===============================================================
class Bat;
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief コウモリの攻撃状態
  */
class BatAttack : public IState
{
// クラス定数の宣言 -------------------------------------------------
public:
	//落下速度
	static constexpr float FALL_SPEED = -0.05f;
// データメンバの宣言 -----------------------------------------------
private:
	// コウモリのポインタ
	Bat* m_bat;
	
	//攻撃モーション
	std::unique_ptr<AttackMotion> m_attackMotion;

	//攻撃音
	std::unique_ptr<Sound> m_attackSound;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	BatAttack(Bat* bat, Wing* pRightWing, Wing* pLeftWing);
	// デストラクタ
	~BatAttack();
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

//　取得・設定
public:

//　内部操作
private:

};

#endif		// BAT_ATTACK_DEFINED
