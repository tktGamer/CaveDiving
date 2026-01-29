/**
 * @file   Game.h
 *
 * @brief  ゲームループに関するヘッダファイル
 *
 * @author 制作者名　
 *
 * @date   日付　2025/09/17
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "DeviceResources.h"
#include "StepTimer.h"
#include"Game/GameData.h"
#include"Game/Common/Graphics.h"
#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"
#include"Game/Object/Gem/GemManager.h"
#include"Game/Shader/Shader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ゲームループ
  */
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
// クラス定数の宣言 -------------------------------------------------
public:

    
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
    //コンストラクタ
    Game() noexcept(false);
    Game(Game&&) = default;
    Game& operator= (Game&&) = default;
    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    //デストラクタ
    ~Game() = default;
//  操作
    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;
//内部処理
private:
    //更新
    void Update(DX::StepTimer const& timer);
    //描画
    void Render();
    //
    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
 // データメンバの宣言 -----------------------------------------------

    // Device resources.
    DX::DeviceResources* m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;
    
    // デバッグ用変数---
    
    //デバッグフォントへのポインタ
    std::unique_ptr<Ito::DebugFont> m_debugFont;
    //デバッグフォントを表示するか
    bool m_isDrawDebugFont;

    //-----------
     
    
    //オーディオ
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
    // キーボードステートトラッカー
    DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

    // マウスステートトラッカー
    DirectX::Mouse::ButtonStateTracker m_mouseTracker;

    // シーン間で渡すゲームに必要なデータ
    std::unique_ptr<GameData> m_gameData;
    // マネージャ関連
    ResourceManager* m_resourceManager;    ///< リソースマネージャ
    std::unique_ptr<SceneManager<GameData>>    m_sceneManager;       ///< シーンマネージャ
    GemManager*      m_gemManager;         ///< 宝石マネージャ
    Graphics* m_graphics;  ///< Graphicsクラスのインスタンス
};