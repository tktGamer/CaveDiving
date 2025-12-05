/**
 * @file   TotalDamage.h
 *
 * @brief  トータルダメージUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/27
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"../NumberControl.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief トータルダメージUI
  */
class TotalDamage
{
	// クラス定数の宣言 -------------------------------------------------
public:


private:
	//描画座標
	DirectX::SimpleMath::Vector2 m_position;
	//トータルダメージ
	std::unique_ptr<NumberControl> m_totalDamageNumber;
	//「トータルダメージ」の文字
	std::unique_ptr<UserInterface> m_totalDamageTexture;

	//アイコンテクスチャの幅
	int m_iconTexureWidth;

	int m_windowWidth, m_windowHeight;

//コンテキスト・デストラクタ
public:
	TotalDamage(const DirectX::SimpleMath::Vector2& pos);
	~TotalDamage();

//操作
public:
	void Initialize(int width, int height, int totalDamage);
	void Update(const int& drawNumber );
	void Render();

};
