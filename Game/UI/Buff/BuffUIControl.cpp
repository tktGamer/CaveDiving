/**
 * @file   BuffUIControl.cpp
 *
 * @brief  バフUI管理に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"BuffUIControl.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Common/Sound.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] width
 * @param[in] height
 */
BuffUIControl::BuffUIControl(int width, int height)
    : 
    m_windowHeight{height},
    m_windowWidth{ width },
    m_nowBuff{},
	m_textureScale{ DirectX::SimpleMath::Vector2::One }
{

}

/**
 * @brief デストラクタ
 */
BuffUIControl::~BuffUIControl()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void BuffUIControl::Initialize()
{


}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void BuffUIControl::Update()
{
    //バフUIの更新
    for (std::unique_ptr<Buff>& buffUI : m_buffUIs) 
    {
        buffUI->Update();
    }

    //残り時間がなくなったバフの表示を消す
    m_buffUIs.remove_if([&](auto&  buff) {return buff->GetRemainingTime() <= 0.0f; });

    //消されたか
    if (m_nowBuff != m_buffUIs.size()) 
    {
        int num = 0;
        //再配置
        for (std::list<std::unique_ptr<Buff>>::iterator it = m_buffUIs.begin(); it != m_buffUIs.end(); ++it) 
        {
            DirectX::SimpleMath::Vector2 buffPos = FIRST_BUFF_UI_POS;
            int row = num % ROW_NUM;
            int col = num / ROW_NUM;

            buffPos.x += row * 105;
            buffPos.y += col * 110;
            (*it)->SetPosition(buffPos);
        }

        m_nowBuff =static_cast<int>( m_buffUIs.size());
    }
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void BuffUIControl::Render()
{
    //バフの描画
    for (std::unique_ptr<Buff>& buffUI : m_buffUIs)
    {
        buffUI->Render();
    }
}

/**
 * @brief バフUIの追加
 *
 * @param[in] upStatus バフの種類
 * @param[in] buffTime バフの効果時間
 *
 * @return なし
 */
void BuffUIControl::AddUI(const Item::EffectType& upStatus, const float& buffTime)
{

    const wchar_t* texturePath{};
	//バフの種類によって画像を変える
    switch (upStatus)
    {
    case Item::EffectType::Attack:
        texturePath = ResourcePath::TEXTURE::UI::ATTACK_BUFF;
        break;
    case Item::EffectType::Diffece:
        texturePath = ResourcePath::TEXTURE::UI::DIFFENCE_BUFF;
        break;
    case Item::EffectType::Outline:
        texturePath = ResourcePath::TEXTURE::UI::OUTLINE_BUFF;
        break;
    default:
        break;
    }

    DirectX::SimpleMath::Vector2 buffPos = FIRST_BUFF_UI_POS;
	//配置位置計算
    int row = m_nowBuff % ROW_NUM;
    int col = m_nowBuff / ROW_NUM;

    buffPos.x += row * NORMAL_SCALE_BUFF_UI_INTERVAL.x * m_textureScale.x;
    buffPos.y += col * NORMAL_SCALE_BUFF_UI_INTERVAL.y * m_textureScale.y;

    m_buffUIs.emplace_back(std::make_unique<Buff>(buffTime,texturePath,buffPos,DirectX::SimpleMath::Vector2{1.0f,1.0f},UserInterface::ANCHOR::MIDDLE_CENTER));
    m_nowBuff++;
}

/**
 * @brief バフUIのサイズ設定
 *
 * @param[in] size バフUIのサイズ
 *
 * @return なし
 */
void BuffUIControl::SetBuffUITextureSize(const DirectX::SimpleMath::Vector2& size)
{
	m_textureScale = size;
}

