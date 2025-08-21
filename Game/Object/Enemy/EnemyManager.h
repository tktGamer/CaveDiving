/**
 * @file   EnemyManager.h
 *
 * @brief  敵管理に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Enemy/Bat/Bat.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief EnemyManager
  */
class EnemyManager
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	//敵配列
	std::list<std::unique_ptr<GameObject>> m_enemies;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	EnemyManager();

	// デストラクタ
	~EnemyManager();


// 操作
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	void Spawn();
//　取得・設定
public:
	//敵を取得
	std::list<std::unique_ptr<GameObject>>& GetEnemies() { return m_enemies; }
//　内部操作
private:

};

