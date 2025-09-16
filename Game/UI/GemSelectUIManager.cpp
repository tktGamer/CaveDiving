/**
 * @file   GemSelectUIManager.cpp
 *
 * @brief  宝石選択のUI群の管理に関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GemSelectUIManager.h"

#include "Game/Common/ResourceManager.h"

#include"Game/Fuctory/UIFactory.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GemSelectUIManager::GemSelectUIManager()
	:m_isClearUI{}
	,m_isPopUI{}
	,m_isPushUI{}
	,m_pushUI{1}
	,m_isDrawOnlyCurrentUI{false}
	,m_isFinishSelect{false}
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
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);


	
	m_uiStack.emplace_back(std::move(UIFactory::CreateHoldGem()));
	m_uiStack.emplace_back(std::move(UIFactory::CreateGemSelect(this)));

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
		ClearUI();
	}
	if (m_isPopUI) 
	{
		PopUI();
	}
	if (!m_pushUI.empty())
	{

		if (m_pushUI[0] != UI::NONE)
		{
			PushUI();
		}
	}


	auto traker = Graphics::GetInstance()->GetKeyboardTracker();
	
	if (traker->pressed.Space)
	{
		//ChangeScene<GameScene,LoadScene>();
	}

	//m_holdGem->Update();
	
	if (!m_uiStack.empty()) 
	{
		m_uiStack.back()->Update();
	}

	//m_gemSelectUI->Update();
	//m_changeGemConfirmUI->Update();

	//m_menu->Update();
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

	//m_holdGem->Render();

	//m_gemSelectUI->Render();
	//m_changeGemConfirmUI->Render();

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

void GemSelectUIManager::RequestPushUI(UI pushUI, bool onlyDraw)
{
	m_pushUI[0] = pushUI;

	m_isDrawOnlyCurrentUI = onlyDraw;
}

void GemSelectUIManager::RequestPopUI()
{
	m_isPopUI = true;
	m_isDrawOnlyCurrentUI = false;

}

void GemSelectUIManager::RequestClearUI()
{
	m_isClearUI = true;
	m_isDrawOnlyCurrentUI = false;

}

bool GemSelectUIManager::IsFinishSelect() const
{
	return m_isFinishSelect;
}

void GemSelectUIManager::SelectFinishNotice()
{
	m_isFinishSelect = true;
}

void GemSelectUIManager::PushUI()
{
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	std::unique_ptr<IUI> ui;

	switch (m_pushUI[0])
	{
	case UI::GEMSELECT:
		ui = UIFactory::CreateGemSelect(this);
		break;
	case UI::CHANGECOFIRM:
		ui = UIFactory::CreateChangeConfirm(this);
		break;
	case UI::CHANGEGEM:
		ui = UIFactory::CreateChangeGem(this); 
		break;
	}

	m_uiStack.emplace_back(std::move(ui));
	m_pushUI[0] = UI::NONE;
}
void GemSelectUIManager::PopUI()
{
	if (!m_uiStack.empty())
	{
		m_uiStack.pop_back();
	}

	m_isPopUI = false;

}

void GemSelectUIManager::ClearUI()
{
	m_uiStack.clear();

	m_isClearUI = false;
}



