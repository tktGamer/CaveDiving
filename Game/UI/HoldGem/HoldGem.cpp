/**
 * @file   HoldGem.cpp
 *
 * @brief  所持している宝石を表示するUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/05
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"HoldGem.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] width  画面幅
 * @param[in] height 画面高さ
 * @param[in] position  描画位置
 * @param[in] scale 　　大きさ
 */
HoldGem::HoldGem(int width, int height,const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale)
    : 
    m_menuIndex{0},
    m_windowHeight{ height },
    m_windowWidth{width},
    m_position{position},
    m_scale{scale},
    m_gemUI{}
{
    SetTextureMap();
}

HoldGem::~HoldGem()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void HoldGem::Initialize()
{
    m_base.reset();
    m_gemUI->reset();

    Add(ResourcePath::TEXTURE::UI::GEM_SLOT,m_position ,m_scale, UserInterface::MIDDLE_CENTER);
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void HoldGem::Update()
{
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void HoldGem::Render()
{
    m_base->Render();
     
    for (int i = 0; i < GEM_NUM; i++)
    {
         //  宝石を表示
         m_gemUI[i]->Render();
    }
}


/**
 * @brief UI設定
 *
 * @param[in] path　　  ファイルパス
 * @param[in] position　座標
 * @param[in] scale　　 拡大率
 * @param[in] anchor    アンカー位置
 *
 * @return なし
 */
void HoldGem::Add(const wchar_t* path,const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale,const UserInterface::ANCHOR& anchor)
{
    //スロットの画像生成
    std::unique_ptr<UserInterface> base = UIFactory::CreateUserInterface(path,position,scale,anchor);
    m_base = std::move(base);
    //表示する宝石UI生成
    for (int i = 0; i < GEM_NUM; i++)
    {
        //大きさを考慮して位置設定
        std::unique_ptr<UserInterface> gem = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::GEM::BLANK_GEM,
            { position.x + GEM_POS_X[i] * scale.x,m_position.y } , GEM_SCALE * scale, anchor);

        m_gemUI[i] = std::move(gem);
    }
}

/**
 * @brief マップ情報設定
 *
 * @param[in]　なし
 *
 * @return なし
 */
void HoldGem::SetTextureMap()
{
    m_gemTextureMap.insert(std::make_pair("エメラルド"  , ResourcePath::TEXTURE::GEM::EMERALD));
    m_gemTextureMap.insert(std::make_pair("ルビー"      , ResourcePath::TEXTURE::GEM::RUBY));
    m_gemTextureMap.insert(std::make_pair("サファイア"  , ResourcePath::TEXTURE::GEM::SAPPHIRE));
    m_gemTextureMap.insert(std::make_pair("トパーズ"    , ResourcePath::TEXTURE::GEM::TOPAZ));
    m_gemTextureMap.insert(std::make_pair("アメジスト"  , ResourcePath::TEXTURE::GEM::AMETHYST));
    m_gemTextureMap.insert(std::make_pair("アクアマリン", ResourcePath::TEXTURE::GEM::AQUAMARINE));
    m_gemTextureMap.insert(std::make_pair("モルガナイト", ResourcePath::TEXTURE::GEM::MORGANITE));
    m_gemTextureMap.insert(std::make_pair("スピネル"    , ResourcePath::TEXTURE::GEM::SPINEL));
}

/**
 * @brief 表示する宝石の変更
 *
 * @param[in] gemID  表示する宝石
 *
 * @return なし
 */
void HoldGem::ChangeDrawGem(const std::vector<int>& gemID)
{
    for (int i = 0; i < gemID.size(); i++)
    {
        const Gem* pGem = GemManager::GetInstance()->GetIDNumberedGem(gemID[i]);
        if (!pGem)
        {
            //もし宝石がなかったら 空用の画像を入れる
            m_gemUI[i]->SetTexture(ResourcePath::TEXTURE::GEM::BLANK_GEM);
            continue;
        }
        //マップから必要なものを取得して設定
        m_gemUI[i]->SetTexture(m_gemTextureMap[pGem->GetAbility().type]);
    }

}


/**
 * @brief 表示位置の変更
 *
 * @param[in] pos  新しい表示位置
 *
 * @return なし
 */
void HoldGem::ChangePositon(const DirectX::SimpleMath::Vector2& pos)
{
    m_position = pos;
    //それぞれのUIの位置を変える
    //スロット
    m_base->SetPosition(m_position);
    //宝石
    for (int i = 0; i < GEM_NUM; i++) 
    {
        m_gemUI[i]->SetPosition({ m_position.x + GEM_POS_X[i] * m_scale.x, m_position.y });
    }
}

void HoldGem::ChangeScale(const DirectX::SimpleMath::Vector2& scale)
{
    m_scale = scale;
    //それぞれのUIの位置を変える
    //スロット
    m_base->SetScale(m_scale);
    //宝石
    for (auto& ui: m_gemUI) 
    {
        ui->SetScale(GEM_SCALE * m_scale);
    }
    //サイズに合わせて位置を調整する
    ChangePositon(m_position);
}

