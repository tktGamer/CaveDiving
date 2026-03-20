/**
 * @file   Operation.cpp
 *
 * @brief  操作方法UIに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/03/20
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Operation.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]　なし
 */
Operation::Operation()
	:
    m_uis{}
{
}

/**
 * @brief デストラクタ
 */
Operation::~Operation()
{
    m_uis.clear();
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Operation::Initialize()
{
    m_uis.clear();
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void Operation::Update()
{
    for (std::unique_ptr<IUI>& ui : m_uis)
    {
        ui->Update();
    }
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void Operation::Render()
{
    for (std::unique_ptr<IUI>& ui : m_uis)
    {
        ui->Render();
    }
}


/**
 * @brief UIの追加
 *
 * @param[in] newUI     UIクラス
 *
 * @return なし
 */
void Operation::AddUI(std::unique_ptr<IUI> newUI)
{
    m_uis.push_back(std::move(newUI));
}
