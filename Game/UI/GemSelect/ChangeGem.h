/**
 * @file   ChangeGem.h
 *
 * @brief  宝石入れ替えUIに関するヘッダファイル
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
#include"../Menu/Menu.h"
#include"../HoldGem/HoldGemInfoDraw.h"
// クラスの宣言 ===============================================================
class Gem;
class GemSelectUIManager;
class HoldGem;
// クラスの定義 ===============================================================
/**
  * @brief 入れ替え確認UI
  */
class ChangeGem : public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	enum MOVE_UI 
	{
		HOLDGEM = 0,
		IS_CHANGI_MENU = 1,

	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//コンストラクタ
	ChangeGem(int width, int height, const std::vector<int>& gemID, GemSelectUIManager* pUIManager);
	//デストラクタ
	~ChangeGem();
// 操作
	//初期化　　　　　　　　
	void Initialize();
	//更新
	void Update() override;
	//描画
	void Render() override;
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	GemSelectUIManager* m_pUIManager;

	std::unique_ptr<UserInterface> m_arrow;
	
	std::unique_ptr<Menu> m_menu;

	int m_windowWidth, m_windowHeight;

	//入れ替え先の宝石
	const Gem* m_pReplacementGem;

	std::unique_ptr<UserInterface> m_replacementGemUI;
	std::unique_ptr<HoldGemInfoDraw> m_holdGemInfo;

	const std::vector<int> m_gemID;

	IUI* m_curremtUI;
};
