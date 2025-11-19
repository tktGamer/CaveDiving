/**
 * @file   DamageSystem.h
 *
 * @brief  ダメージシステムに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付 2025/08/22
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


// データメンバの宣言 -----------------------------------------------
private:
	// DamageSystemクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<DamageSystem> s_damageSystem;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
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

	// デストラクタ
	~DamageSystem();


// 操作
public:
	// DamageSystemクラスのインスタンスを取得する
	static DamageSystem* const GetInstance();

	//ダメージ処理
	int DamageToCharacter(Character* attacker,Character* defender);

	//ダメージ計算
	int DamageCalculation(const int attackPower, const int diffence);
//　取得・設定
public:

//　内部操作
private:

};

