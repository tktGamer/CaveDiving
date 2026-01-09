/**
 * @file   Buff.h
 *
 * @brief  適用中のバフ表示UIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/10/10
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"Game/Object/Gem/GemManager.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 適用中のバフ表示UI
  */
class Buff
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:


	std::unique_ptr<UserInterface> m_upType;
	std::unique_ptr<UserInterface> m_frame;


	const wchar_t* m_baseTexturePath;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	//バフの残り時間
	const float* m_remainingTime;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	Buff(const float& time);
	~Buff();
// 操作
public:

	void Initialize(const wchar_t* path, int width, int height);
	void Update();
	void Render();

	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);
	
// 取得/設定
public:
	const float& GetRemainingTime();

	void SetPosition(const DirectX::SimpleMath::Vector2& pos);
//内部処理
private:
};
