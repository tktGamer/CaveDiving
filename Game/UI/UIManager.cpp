/**
 * @file   UIManager.cpp
 *
 * @brief  宝石選択のUI群の管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/14
 */
// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UIManager.h"
#include "Game/Common/ResourceManager.h"
#include"Game/Factory/UIFactory.h"

std::unique_ptr<UIManager> UIManager::s_uiManager = nullptr;

/**
 * @brief クラスのインスタンスを取得する
 *
 * @param[in] なし
 *
 * @return クラスのインスタンスへのポインタ
 */
UIManager* const UIManager::GetInstance()
{
	if (!s_uiManager)
	{
		s_uiManager.reset(new UIManager());
	}
	return s_uiManager.get();
}
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
UIManager::UIManager()
	:m_isClearUI{},
	m_isDrawOnlyCurrentUI{},
	m_isFinishSelect{},
	m_isPopUI{},
	m_isPushUI{}

{

}



/**
 * @brief デストラクタ
 */
UIManager::~UIManager()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::Initialize()
{
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::Update()
{
	//UIの追加・破棄　＊追加を最後にすること
	if (m_isClearUI) 
	{
		//全UI消去
		ClearUI();
	}
	if (m_isPopUI) 
	{
		//UI消去
		//PopUI();
	}
	if (!m_pushUI.empty())
	{
		//UI追加
		if (m_pushUI[0] != UI::NONE)
		{
			PushUI();
		}
	}

	
	//UI更新
	for (std::unique_ptr<IUI>& ui : m_uiStack)
	{
		ui->Update();
	}

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::Render()
{


	//1つのUIだけ描画するか
	if (m_isDrawOnlyCurrentUI) 
	{
		m_uiStack.back()->Render();
	}
	else
	{
		for (auto& ui : m_uiStack)
		{
			ui->Render();
		}
	}

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::Finalize()
{
	m_uiStack.clear();
}

/**
 * @brief UI追加リクエスト
 *
 * @param[in] pushUI    追加するUIの種類
 * @param[in] onlyDraw  そのUIのみ表示するか
 *
 * @return なし
 */
void UIManager::RequestAddUI(std::unique_ptr<IUI> ui, bool isOnlyDraw)
{
	m_uiStack.push_back(std::move(ui));
	m_isDrawOnlyCurrentUI = isOnlyDraw;
}

/**
 * @brief UI消去リクエスト
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::RequestPopUI()
{
	m_isPopUI = true;
	m_isDrawOnlyCurrentUI = false;

}


/**
 * @brief 全UI消去リクエスト
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::RequestClearUI()
{
	m_isClearUI = true;
	m_isDrawOnlyCurrentUI = false;

}




/**
 * @brief UI追加処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::PushUI()
{
	//int w, h;
	//Graphics::GetInstance()->GetScreenSize(w, h);

	//std::unique_ptr<IUI> ui;

	//switch (m_pushUI[0])
	//{
	//case UI::GEMSELECT:
	//	ui = UIFactory::CreateGemSelect(this,m_gemID);
	//	break;
	//case UI::CHANGECOFIRM:
	//	ui = UIFactory::CreateChangeConfirm(this);
	//	break;
	//case UI::CHANGEGEM:
	//	ui = UIFactory::CreateChangeGem(this,m_gemID); 
	//	break;
	//}

	//m_uiStack.emplace_back(std::move(ui));
	//m_pushUI[0] = UI::NONE;
}


/**
 * @brief 全UI消去処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void UIManager::ClearUI()
{
	m_uiStack.clear();

	m_isClearUI = false;
}



