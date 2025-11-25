/**
 * @file   AttackMotion.h
 *
 * @brief  攻撃モーションの基底に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付 2025/11/21
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Motion/Motion.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 攻撃モーションの基底
  */
class AttackMotion : public Motion
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	//モーションによる攻撃力の補正
	float m_attackPowerModifier;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	AttackMotion(const float& attackPowerModifier);

	// デストラクタ
	virtual ~AttackMotion();


// 操作
public:
	//初期化
	virtual void Initialize()=0;

	//更新
	virtual bool Update() = 0;

	//リセット
	virtual void Reset();

//　取得・設定
public:
	float GetAttackPowerModifier() const;

	void SetAttackPowerModifier(const float& modifier);
//　内部操作
private:

};

