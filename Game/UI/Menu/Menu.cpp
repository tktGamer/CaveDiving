/**
 * @file   Menu.cpp
 *
 * @brief  選択UIに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/30
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Menu.h"
#include"Game/Common/Sound.h"
#include"Game/Factory/UIFactory.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] cursolSound
 */
Menu::Menu(DirectX::SoundEffect* cursolSound)
    : 
    m_menuIndex(0),
    m_baseTexturePath(nullptr),
    m_cursorSound{},
    m_userInterface{},
    m_base{}
{
    m_cursorSound = std::make_unique<Sound>(cursolSound);
    m_userInterface.clear();
}


/**
 * @brief デストラクタ
 */
Menu::~Menu()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in]なし
 *
 * @return なし
 */
void Menu::Initialize()
{
    //  背景となるウィンドウ画像を読み込む
    m_baseTexturePath = ResourcePath::TEXTURE::UI::MENU_FRAME;
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void Menu::Update()
{
    //UIがなかったら処理しない
    if (m_userInterface.empty()) return;

    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();
    if (tracker->pressed.Right)
    {
        //  →キーを押したら、選択先を1つ進める
        m_menuIndex += 1;
        //  メニューアイテム数の最大値を超えないように制御
        m_menuIndex %= m_userInterface.size();

        m_cursorSound->Play(false);
    }
    if (tracker->pressed.Left)
    {
        //  ←キーを押したら、選択先を1つ戻す。
        //  ただし、選択先のオーバーを割り算の余りで補正するため、（アイテムの最大個数 - 1）を足して必ず余りで計算する形にしておく。
        //  以下の式は、例えばメニューが4つあったら、現在値に3を足すという事。
        //  例）選択中のメニューが0～3まである内の2番目だった場合、
        //  (2 + (4 - 1)) % 4 = 1 ← 選択中の番号が1つ減った
        //  ということ
        m_menuIndex += static_cast<unsigned int>(m_userInterface.size()) - 1;
        m_menuIndex %= m_userInterface.size();

        m_cursorSound->Play(false);

    }


    //  各アイテムに表示する画像の初期サイズを設定する
    for (int i = 0; i < m_userInterface.size(); i++)
    {
        m_base[i]->SetScale(m_base[i]->GetBaseScale());
        m_userInterface[i]->SetScale(m_userInterface[i]->GetBaseScale());
    }

    //  選択中の初期サイズを取得する
    DirectX::SimpleMath::Vector2 select = m_userInterface[m_menuIndex]->GetBaseScale();
    //  選択状態とするための変化用サイズを算出する
    DirectX::SimpleMath::Vector2 selectScale = DirectX::SimpleMath::Vector2::Lerp(m_userInterface[m_menuIndex]->GetBaseScale(), DirectX::SimpleMath::Vector2::One, 1);
    //  選択状態は初期状態＋30％の大きさとする
    select += selectScale * 0.3f;
    //  算出後のサイズを現在のサイズとして設定する
    m_userInterface[m_menuIndex]->SetScale(select);
    //  背景用のウィンドウ画像にも同じ割合の値を設定する
    m_base[m_menuIndex]->SetScale(select);
}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void Menu::Render()
{
    for (int i = 0; i < m_userInterface.size(); i++)
    {
        //  アイテム用ウィンドウ背景を表示
        m_base[i]->Render();
        //  実際に表示したいアイテム画像を表示
        m_userInterface[i]->Render();
    }
}

/**
 * @brief メニュー追加
 *
 * @param[in] path　　　画像パス
 * @param[in] position　描画位置
 * @param[in] scale　　 大きさ
 * @param[in] anchor　　アンカー位置
 *
 * @return なし
 */
void Menu::Add(const wchar_t* path, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor)
{
    //  メニューとしてアイテムを追加する
    std::unique_ptr<UserInterface> userInterface = UIFactory::CreateUserInterface(path,position,scale,anchor);
    //  アイテムを新しく追加
    m_userInterface.push_back(std::move(userInterface));

    //  背景用のウィンドウ画像も追加する
    std::unique_ptr<UserInterface> base = UIFactory::CreateUserInterface(m_baseTexturePath,position,scale,anchor);
    //  背景用のアイテムも新しく追加する
    m_base.push_back(std::move(base));
}
/**
 * @brief メニュー追加
 *
 * @param[in] info  追加するメニューの情報
 *
 * @return なし
 */
void Menu::Add(const MunuUIInfo& info)
{
    //  メニューとしてアイテムを追加する
    std::unique_ptr<UserInterface> userInterface = UIFactory::CreateUserInterface(info.path, info.position, info.scale, info.anchor);
    //  アイテムを新しく追加
    m_userInterface.push_back(std::move(userInterface));

    //  背景用のウィンドウ画像も追加する
    std::unique_ptr<UserInterface> base = UIFactory::CreateUserInterface(m_baseTexturePath, info.position, info.scale, info.anchor);
    //  背景用のアイテムも新しく追加する
    m_base.push_back(std::move(base));

}
