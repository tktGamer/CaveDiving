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
		IS_CHANGI_MENU = 0,
		HOLDGEM = 1,

	};
	//非公開定数
private:
	//矢印UIの位置
	static constexpr DirectX::SimpleMath::Vector2 ARROW_POSITION = { 650.0f,200.0f };
	//矢印UIの大きさ
	static constexpr DirectX::SimpleMath::Vector2 ARROW_SCALE = { 0.8f,0.8f };
	//「入れ替える」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 CHANGE_MESSAGE_POSITION = { 500.0f,600.0f };
	//「入れ替える」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 CHANGE_MESSAGE_SCALE = { 0.8f,0.8f };
	//「戻る」のメッセージの位置
	static constexpr DirectX::SimpleMath::Vector2 RETURN_MESSAGE_POSITION = { 850.0f,600.0f };
	//「戻る」のメッセージの大きさ
	static constexpr DirectX::SimpleMath::Vector2 RETURN_MESSAGE_SCALE = { 0.8f,0.8f };
	//入れ替え先宝石UIの位置
	static constexpr DirectX::SimpleMath::Vector2 REPLACE_GEM_UI_POSITION = { 950.0f,200.0f };
	//入れ替え先宝石UIの大きさ
	static constexpr DirectX::SimpleMath::Vector2 REPLACE_GEM_UI_SCALE = { 1.0f,1.0f };

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
