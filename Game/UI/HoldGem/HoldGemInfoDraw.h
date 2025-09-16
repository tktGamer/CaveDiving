/**
 * @file   HoldGemInfoDraw.h
 *
 * @brief  所持している宝石の内1つの情報を表示するUIに関するヘッダファイル
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
#include"Game/UI/HoldGem/HoldGem.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 所持している宝石の内1つの情報を表示するUI
  */
class HoldGemInfoDraw : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	//宝石の表示位置
	static constexpr float GEM_POS_X[3] = {-46.0f, 0.0f ,46.0f};
	static constexpr DirectX::SimpleMath::Vector2 GEM_SCALE = {0.13f,0.13f};
// データメンバの宣言 -----------------------------------------------
private:
	GemManager* m_pGemManager;

	unsigned int m_menuIndex;
	const wchar_t* m_gemTexturePath;

	std::unique_ptr<UserInterface> m_gemUI[3];
	std::unique_ptr<UserInterface> m_base;


	std::unique_ptr<UserInterface> m_cursol;

	int m_windowWidth, m_windowHeight;


	Gem* m_pGems[3];

	DirectX::SimpleMath::Vector2 m_position;
	DirectX::SimpleMath::Vector2 m_scale;

	std::unique_ptr<HoldGem> m_holdGem;
	//入れ替え候補の宝石UI
	std::unique_ptr<UserInterface> m_candidateGemUI;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	HoldGemInfoDraw(int width, int height);
	~HoldGemInfoDraw();
	// 操作
public:
	void Initialize();
	void Update();
	void Render();

	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);

	void ChangePositon(const DirectX::SimpleMath::Vector2& pos);
	void ChangeScale(const DirectX::SimpleMath::Vector2& scale);
//　取得・設定
public:


//　内部操作
private:
};
