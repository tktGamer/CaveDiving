/**
 * @file   HoldGemInfoDraw.cpp
 *
 * @brief  所持している宝石の内1つの情報を表示するUIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include"HoldGemInfoDraw.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] width
 * @param[in] height
 */
HoldGemInfoDraw::HoldGemInfoDraw(int width, int height, const std::vector<int>& gemID)
    : 
    m_menuIndex(0),
    m_windowHeight(height),
    m_windowWidth(width),
    m_position{ 80,680 },
    m_scale{ 1.0f,1.0f },
    m_gemID{gemID}
{

}

/**
 * @brief デストラクタ
 */
HoldGemInfoDraw::~HoldGemInfoDraw()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void HoldGemInfoDraw::Initialize()
{

    //所持宝石UI生成
    m_holdGem = UIFactory::CreateHoldGem(m_gemID, HOLD_GEM_UI_POS,HOLD_GEM_UI_SCALE);
    //カーソルUI生成
    m_cursol = UIFactory::CreateUserInterface(ResourcePath::TEXTURE::UI::RED_CURSOL, CURSOL_UI_POS, CURSOL_UI_SCALE, UserInterface::ANCHOR::MIDDLE_CENTER);

    //入れ替え候補宝石UI
    m_candidateGemUI = UIFactory::CreateUserInterface(
        GemManager::GetInstance()->GetIDNumberedGem(m_gemID[m_menuIndex])->GetImagePath().panel,
        CACDIDATE_GEM_UI_POS,
        DirectX::SimpleMath::Vector2::One,
        UserInterface::MIDDLE_CENTER);

}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void HoldGemInfoDraw::Update()
{
    m_holdGem->Update();

    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

    static float time;
    time += Messenger::GetInstance()->GetElapsedTime();

    if (tracker->pressed.Right)
    {
        //  →キーを押したら、選択先を1つ進める
        m_menuIndex += 1;
        //  メニューアイテム数の最大値を超えないように制御
        m_menuIndex %= GemManager::PLAYER_HOLD_GEM_NUM;
    }
    if (tracker->pressed.Left)
    {
        //  ←キーを押したら、選択先を1つ戻す。
        //  ただし、選択先のオーバーを割り算の余りで補正するため、（アイテムの最大個数 - 1）を足して必ず余りで計算する形にしておく。
        //  以下の式は、例えばメニューが4つあったら、現在値に3を足すという事。
        //  例）選択中のメニューが0～3まである内の2番目だった場合、
        //  (2 + (4 - 1)) % 4 = 1 ← 選択中の番号が1つ減った
        //  ということ
        m_menuIndex += static_cast<unsigned int>(GemManager::PLAYER_HOLD_GEM_NUM) - 1;
        m_menuIndex %= GemManager::PLAYER_HOLD_GEM_NUM;
    }

    m_candidateGemUI->SetTexture(GemManager::GetInstance()->GetIDNumberedGem(m_gemID[m_menuIndex])->GetImagePath().panel);

    m_cursol->SetPosition({ CURSOL_UI_POS.x + HoldGem::GEM_POS_X[m_menuIndex]*2.0f ,CURSOL_UI_POS.y });
    float scale = abs(std::sin(time)) + 1.0f;
    m_cursol->SetScale({ scale,scale });
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void HoldGemInfoDraw::Render()
{
    m_holdGem->Render();
    //表示している宝石を選ぶカーソル
    m_cursol->Render();
    //選ばれている宝石を表示
    m_candidateGemUI->Render();
}


/**
 * @brief 位置設定
 *
 * @param[in] pos  位置
 *
 * @return なし
 */
void HoldGemInfoDraw::SetPositon(const DirectX::SimpleMath::Vector2& pos)
{
    m_position = pos;
}

/**
 * @brief 大きさ設定
 *
 * @param[in] scale
 *
 * @return なし
 */
void HoldGemInfoDraw::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
    m_scale = scale;
}
/**
 * @brief 選択さえれているものの番号
 *
 * @param[in] scale
 *
 * @return なし
 */
int HoldGemInfoDraw::GetMunuIndex() const
{
    return m_menuIndex;
}