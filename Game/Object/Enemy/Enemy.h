/**
 * @file   Enemy.h
 *
 * @brief  敵に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/04/02
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Object/Character.h"
// クラスの宣言 ===============================================================
class EnemyManager;
// クラスの定義 ===============================================================
/**
  * @brief 敵
  */
class Enemy : public Character
{
// クラス定数の宣言 -------------------------------------------------
public:


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Enemy(EnemyManager* enemyManager, int hp, int attack, int diffence,
		const GameObject3D* parent, const Transform& transform,
		const std::vector<int>& gemID);

	// デストラクタ
	~Enemy();
// 操作
public:
	//死んだときの処理
	void OnDead();
//　取得・設定
public:

//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//管理クラスのポインタ
	EnemyManager* m_pEnemyManager;
};

