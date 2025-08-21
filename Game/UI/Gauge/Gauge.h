/**
 * @file   Gauge.h
 *
 * @brief  ゲージUIに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"Game/Object/Gem/GemManager.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ユーザーインターフェイス
  */

class Gauge
{
public:


private:


	std::unique_ptr<UserInterface> m_gauge;
	std::unique_ptr<UserInterface> m_frame;


	const wchar_t* m_baseTexturePath;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	//ゲージの参照する値
	const int* m_currentValue;
	const int* m_maxValue;
public:
	Gauge();
	~Gauge();

	void Initialize(int width, int height);
	void Update();
	void Render();

	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);

	void SetValue(const int& current, const int& max);

};
