/**
 * @file   EnemyManager.h
 *
 * @brief  敵管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/19
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================
class Character;
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief 敵管理
  */
class EnemyManager
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開
private:
	//コウモリ
	static constexpr char BAT[] = "コウモリ";
	//ゴーレム
	static constexpr char GOLEM[] = "ゴーレム";
	//落下判定
	static constexpr float DEAD_LINE = -50.0f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//残りの敵の数を取得
	const int GetEnemyCount() const;
	//残りの敵の数を設定
	void SetEnemyCount(const int& count);
	//敵残数減少
	void DecreaseEnemyCount();
// コンストラクタ/デストラクタ
	// コンストラクタ
	EnemyManager();
	// デストラクタ
	~EnemyManager();
// 操作
	//初期化処理
	void Initialize();
	//終了処理
	void Finalize();
	//敵生成
	std::vector<std::unique_ptr<Character>> Spawn(const std::string& spawnData);
//　内部操作
private:
	//敵が範囲外にいるか
	bool IsOutOfStage(const Character* enemy);
// データメンバの宣言 -----------------------------------------------
private:
	//敵残数
	int m_enemyCount;
	//消滅音
	std::unique_ptr<Sound> m_vanishSound;
};