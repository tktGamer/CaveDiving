/**
 * @file   GemSelect.h
 *
 * @brief  宝石選択UIに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "../UserInterface.h"
#include"Game/Interface/IUI.h"

// クラスの宣言 ===============================================================
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief メニューUI
  */
class Menu : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:

	
// データメンバの宣言 -----------------------------------------------
private:

	unsigned int m_menuIndex;

	std::vector<std::unique_ptr<UserInterface>> m_userInterface;
	std::vector<std::unique_ptr<UserInterface>> m_base;

	const wchar_t* m_baseTexturePath;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	//効果音
	std::unique_ptr<Sound> m_cursorSound;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	Menu(int width, int height,DirectX::SoundEffect* cursolSound);
	~Menu();

	void Initialize();
	void Update();
	void Render();

	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);

//　取得・設定
public:
	int GetMenuIndex() const { return m_menuIndex; }
};
