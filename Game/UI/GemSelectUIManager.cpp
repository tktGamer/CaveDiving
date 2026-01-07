/**
 * @file   GemSelectUIManager.cpp
 *
 * @brief  宝石選択のUI群の管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/16
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GemSelectUIManager.h"

#include "Game/Common/ResourceManager.h"

#include"Game/Factory/UIFactory.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GemSelectUIManager::GemSelectUIManager(const std::vector<int>& gemID)
	:m_isClearUI{}
	,m_isPopUI{}
	,m_isPushUI{}
	,m_pushUI{1}
	,m_isDrawOnlyCurrentUI{false}
	,m_isFinishSelect{false}
	,m_gemID{gemID}
{

}



/**
 * @brief デストラクタ
 */
GemSelectUIManager::~GemSelectUIManager()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::Initialize()
{

	//初期状態のUI追加
	m_uiStack.emplace_back(std::move(UIFactory::CreateHoldGem(m_gemID)));
	m_uiStack.emplace_back(std::move(UIFactory::CreateGemSelect(this,m_gemID)));

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::Update()
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
		PopUI();
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
	if (!m_uiStack.empty()) 
	{
		m_uiStack.back()->Update();
	}

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::Render()
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
void GemSelectUIManager::Finalize()
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
void GemSelectUIManager::RequestPushUI(UI pushUI, bool onlyDraw)
{
	m_pushUI[0] = pushUI;

	m_isDrawOnlyCurrentUI = onlyDraw;
}

/**
 * @brief UI消去リクエスト
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::RequestPopUI()
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
void GemSelectUIManager::RequestClearUI()
{
	m_isClearUI = true;
	m_isDrawOnlyCurrentUI = false;

}


/**
 * @brief 宝石選択が終了したか
 *
 * @param[in] なし
 *
 * @return true　終了
 * @return false 未了
 */
bool GemSelectUIManager::IsFinishSelect() const
{
	return m_isFinishSelect;
}


/**
 * @brief 宝石選択終了知らせ
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::SelectFinishNotice(int slotNum)
{
	m_isFinishSelect = true;
	m_slot = slotNum;
}

void GemSelectUIManager::SetHoldGem(const Gem* pGem)
{
	m_pReplacementGem = pGem;
}

const Gem* GemSelectUIManager::GetHoldGem()
{
	return m_pReplacementGem;
}

int GemSelectUIManager::GetSlot()
{
	return m_slot;
}


/**
 * @brief UI追加処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::PushUI()
{
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	std::unique_ptr<IUI> ui;

	switch (m_pushUI[0])
	{
	case UI::GEMSELECT:
		ui = UIFactory::CreateGemSelect(this,m_gemID);
		break;
	case UI::CHANGECOFIRM:
		ui = UIFactory::CreateChangeConfirm(this);
		break;
	case UI::CHANGEGEM:
		ui = UIFactory::CreateChangeGem(this,m_gemID); 
		break;
	}

	m_uiStack.emplace_back(std::move(ui));
	m_pushUI[0] = UI::NONE;
}

/**
 * @brief UI消去処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::PopUI()
{
	if (!m_uiStack.empty())
	{
		m_uiStack.pop_back();
	}

	m_isPopUI = false;

}


/**
 * @brief 全UI消去処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemSelectUIManager::ClearUI()
{
	m_uiStack.clear();

	m_isClearUI = false;
}



