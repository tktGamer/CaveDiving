/**
 * @file   DamageSystem.h
 *
 * @brief  ダメージシステムに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/17
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Graphics.h"
#include "Game/Object/GameObject.h"
#include"Game/Object/Character.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ダメージシステム
  */
class DamageSystem
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//プレイヤーが与えたトータルダメージの取得
	int GetTotalDamage() const;
	//トータルダメージのリセット
	void ResetTotalDamage();
//デストラクタ
	// デストラクタ
	~DamageSystem();
// 操作
	// DamageSystemクラスのインスタンスを取得する
	static DamageSystem* const GetInstance();
	//ダメージ処理
	int DamageToCharacter(const Character* attacker, Character* defender);
	//ダメージ計算
	int DamageCalculation(const int attackPower, const int diffence);
//コンストラクタ
private:
	// コンストラクタ
	DamageSystem();
	// インスタンスをコピーすることを禁止する
	void operator=(const DamageSystem&) = delete;
	// インスタンスをムーブすることを禁止する
	DamageSystem& operator= (DamageSystem&&) = delete;
	// コピーコンストラクタは禁止する
	DamageSystem(const DamageSystem&) = delete;
	// ムーブコンストラクタは禁止する
	DamageSystem(DamageSystem&&) = delete;
//　内部操作

// データメンバの宣言 -----------------------------------------------
private:
	// DamageSystemクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<DamageSystem> s_damageSystem;
	//プレイヤーが与えたトータルダメージ
	int m_totalDamage;
};

