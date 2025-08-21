//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include"Game/UserResources.h"
#include"Game/Common/Graphics.h"
#include "Game/Common/ResourceManager.h"
#include "Game/Common/SceneManager.h"
#include"Game/Object/Gem/GemManager.h"
#include"Game/Shader.h"
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

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

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    DX::DeviceResources* m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    //�I�[�f�B�I
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
    //�f�o�b�O�t�H���g�ւ̃|�C���^
    std::unique_ptr<Ito::DebugFont> m_debugFont;
    // �L�[�{�[�h�X�e�[�g�g���b�J�[
    DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

    // �}�E�X�X�e�[�g�g���b�J�[
    DirectX::Mouse::ButtonStateTracker m_mouseTracker;

    // �}�l�[�W���֘A
    ResourceManager* m_resourceManager;    ///< ���\�[�X�}�l�[�W��
    std::unique_ptr<SceneManager<UserResources>>    m_sceneManager;       ///< �V�[���}�l�[�W��
    GemManager*      m_gemManager;         ///< ��΃}�l�[�W��
    Graphics* m_graphics;  ///< Graphics�N���X�̃C���X�^���X
    // �V�[���֓n�����[�U�[��`�̃��\�[�X�ւ̃|�C���^
    std::unique_ptr<UserResources> m_userResources;

};
