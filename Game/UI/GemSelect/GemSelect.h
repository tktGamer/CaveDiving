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
#include"Game/Object/Gem/GemManager.h"
#include"Game/Interface/IUI.h"
// クラスの宣言 ===============================================================
class GemSelectUIManager;
class Sound;
// クラスの定義 ===============================================================
/**
  * @brief ユーザーインターフェイス
  */
class GemSelect : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr float PANNEL_X = 310.0f;
	//宝石抽選の最大回数
	static constexpr int MAX_TRY = 100;

// データメンバの宣言 -----------------------------------------------
private:
	GemSelectUIManager* m_pUIManager;

	GemManager* m_pGemManager;

	unsigned int m_menuIndex;

	std::vector<std::unique_ptr<UserInterface>> m_userInterface;
	std::vector<std::unique_ptr<UserInterface>> m_base;

	const wchar_t* m_baseTexturePath;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	DirectX::Keyboard::KeyboardStateTracker m_tracker;

	const Gem* m_pGems[3];

	//効果音
	std::unique_ptr<Sound> m_cursorSound;
	std::unique_ptr<Sound> m_decideSound;

	const std::vector<int> m_gemID;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	GemSelect(int width, int height,const std::vector<int>& gemID, GemSelectUIManager* pUIManager);
	~GemSelect();
	// 操作
public:
	void Initialize() ;
	void Update() override;
	void Render() override;

	void Add(Gem::GemImagePath gemImagePath
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);

	//宝石をランダムに選択
	void Randomize();

	
//　取得・設定
public:

	int GetGemSelectIndex() const { return m_menuIndex; }

//　内部操作
private:

};
