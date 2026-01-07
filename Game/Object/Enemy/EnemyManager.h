/**
 * @file   EnemyManager.h
 *
 * @brief  敵管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/04
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../Enemy/Bat/Bat.h"
#include"../Enemy/Golem/Golem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 敵管理
  */
class EnemyManager
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:

	//敵リスト
	std::list<std::unique_ptr<Character>> m_enemies;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	EnemyManager();

	// デストラクタ
	~EnemyManager();


// 操作
public:
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//終了処理
	void Finalize();

	//敵生成
	void Spawn(const std::string& spawnData);

//　取得・設定
public:
	//敵を取得
	const std::list<std::unique_ptr<Character>>& GetEnemies() { return m_enemies; }
//　内部操作
private:
	//敵を消去
	void DeleteEnemy();
};

