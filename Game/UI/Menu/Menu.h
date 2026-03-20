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
	//選択肢の情報
	struct MunuUIInfo 
	{
		const wchar_t* path;
		DirectX::SimpleMath::Vector2 position;
		DirectX::SimpleMath::Vector2 scale;
		UserInterface::ANCHOR anchor;
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//選んでいる選択の番号の取得
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
	//選択肢追加
	void Add(const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const UserInterface::ANCHOR& anchor);
	void Add(const MunuUIInfo& info);
// データメンバの宣言 -----------------------------------------------
private:

	unsigned int m_menuIndex;
	//表示する内容
	std::vector<std::unique_ptr<UserInterface>> m_userInterface;
	//フレーム
	std::vector<std::unique_ptr<UserInterface>> m_base;

	const wchar_t* m_baseTexturePath;

	//効果音
	std::unique_ptr<Sound> m_cursorSound;
};
