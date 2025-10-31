/**
 * @file   ClearConditions.h
 *
 * @brief  クリア条件UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/09/12
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"../NumberControl.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief クリア条件UI
  */
class ClearConditions
{
	// クラス定数の宣言 -------------------------------------------------
public:


private:
	//描画座標
	DirectX::SimpleMath::Vector2 m_position;
	//残りの敵の数
	std::unique_ptr<NumberControl> m_restEnemy;
	//敵のアイコン
	std::unique_ptr<UserInterface> m_enemyIcon;

	//アイコンテクスチャの幅
	int m_iconTexureWidth;

	int m_windowWidth, m_windowHeight;

//コンテキスト・デストラクタ
public:
	ClearConditions(const DirectX::SimpleMath::Vector2& pos);
	~ClearConditions();

//操作
public:
	void Initialize(int width, int height);
	void Update(const int& drawNumber );
	void Render();

};
