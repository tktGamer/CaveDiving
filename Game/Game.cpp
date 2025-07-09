//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include"Game/Scene/TitleScene.h"
#include"Game/Scene/GameScene.h"
extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
    : m_resourceManager{}
    , m_sceneManager{}
    , m_gemManager{}
    , m_audioEngine{}
    , m_graphics{}

{
    m_graphics = Graphics::GetInstance();
    m_deviceResources = m_graphics->GetDeviceResources();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    //�I�[�f�B�I�G���W���̍쐬
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif // DEBUG
    m_audioEngine = std::make_unique<AudioEngine>(eflags);
    m_audioEngine->SetMasterVolume(1.0f); // 1.0f�͍ő剹��


    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

    m_graphics->Initialize();

	m_gemManager = std::make_unique<GemManager>();
	m_gemManager->Initialize();
    //�V�[������
	m_sceneManager->Register("Title", std::make_unique<TitleScene>(m_sceneManager.get()));
	m_sceneManager->Register("Game", std::make_unique<GameScene>(m_sceneManager.get()));
    //�J�n�V�[���ݒ�
	m_sceneManager->SetStratScene("Title");
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
    // ���b�Z���W���[�Ɍo�ߎ��Ԃ�ݒ肷��
    Messenger::GetInstance()->SetElapsedTime(elapsedTime);


    auto key = Keyboard::Get().GetState();
	m_graphics->UpdateKeyboardTracker(key);
    //�V�[���̍X�V
    m_sceneManager->Update(elapsedTime);


    // �I�[�f�B�I�̍X�V
    if (!m_audioEngine->Update())
    {
        if (m_audioEngine->IsCriticalError())
        {
            // �G���[����
            OutputDebugString(L"AudioEngine Error\n");
        }
    }

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    //�V�[���̕`��
    m_sceneManager->Render();


    std::wostringstream str;
    str << L"fps: " << m_timer.GetFramesPerSecond();
    m_debugFont->AddString(str.str().c_str(), DirectX::SimpleMath::Vector2::Zero);
    m_debugFont->Render(m_graphics->GetCommonStates());

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
    m_audioEngine->Suspend();

}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
	m_audioEngine->Resume();
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

    //�}�l�[�W���[����
    m_resourceManager = ResourceManager::GetInstance();
    m_sceneManager = std::make_unique<SceneManager>();

	m_resourceManager->SetAudioEngine(m_audioEngine.get());

    Shader* shader = Shader::GetInstance();
    m_debugFont = std::make_unique<Ito::DebugFont>(device, context, L"Resources\\Font\\SegoeUI_18.spritefont");

	m_graphics->SetDebugFont(m_debugFont.get());
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
        // ��ʃT�C�Y�̎擾
    RECT rect = m_deviceResources->GetOutputSize();

    // �ˉe�s��̍쐬
    auto proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        XMConvertToRadians(45.0f)
        , static_cast<float>(rect.right) / static_cast<float>(rect.bottom)
        , 0.1f, 100.0f);
    m_graphics->SetProjectionMatrix(proj);

}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
