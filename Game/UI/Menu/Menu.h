/**
 * @file   Menu.h
 *
 * @brief  メニューUIに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
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

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	int GetMenuIndex() const { return m_menuIndex; }
// コンストラクタ/デストラクタ
public:
	//コンストラクタ
	Menu(DirectX::SoundEffect* cursolSound);
	//デストラクタ
	~Menu();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();

	void Add(const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const UserInterface::ANCHOR& anchor);
// データメンバの宣言 -----------------------------------------------
private:

	unsigned int m_menuIndex;

	std::vector<std::unique_ptr<UserInterface>> m_userInterface;
	std::vector<std::unique_ptr<UserInterface>> m_base;

	const wchar_t* m_baseTexturePath;

	//効果音
	std::unique_ptr<Sound> m_cursorSound;
};
