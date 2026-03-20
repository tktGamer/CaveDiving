/**
 * @file   Key.cpp
 *
 * @brief  キーUIに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/03/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Key.h"
#include"Game/Message/Messenger.h"
#include"Game/Factory/UIFactory.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/UI/UIManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] respoceKey 反応するキー
 */
Key::Key(const std::vector<DirectX::Keyboard::Keys>& respoceKey)
	:
    UserInterface{},
    m_responceKey{respoceKey},
    m_isKeyPressed{false}
{
}

/**
 * @brief デストラクタ
 */
Key::~Key()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Key::Initialize()
{
}

/**
 * @brief 更新
 *
 * @param[in] なし
 *
 * @return なし
 */
void Key::Update()
{
   
    DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();
    for (auto key : m_responceKey) 
    {
        //設定されたキーが押されていたら
        if (traker->GetLastState().IsKeyDown(key)) 
        {
            m_isKeyPressed = true;
            break;
        }
        else
        {
            m_isKeyPressed = false;
        }
    }

}

/**
 * @brief 描画
 *
 * @param[in] なし
 *
 * @return なし
 */
void Key::Render()
{

    ShaderManager* shader = ShaderManager::GetInstance();
    DirectX::CommonStates* states = Graphics::GetInstance()->GetCommonStates();

    ID3D11DeviceContext1* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    //	頂点情報
    //	Position.xy	:拡縮用スケール
    //	Position.z	:アンカータイプ(0～8)の整数で指定
    //	Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
    //	Color.zw	:画像サイズ
    //	Tex.xy		:x = 0, y = 0
    DirectX::VertexPositionColorTexture vertex[1] = {
        DirectX::VertexPositionColorTexture(
             DirectX::SimpleMath::Vector3(GetScale().x, GetScale().y, static_cast<float>(GetAnchor()))
            ,DirectX::SimpleMath::Vector4(GetPosition().x, GetPosition().y, GetTextureSize().x,GetTextureSize().y)
            ,DirectX::SimpleMath::Vector2(0,0))
    };
    //	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
    KeyUIShader::KeyUICB cbuff;
    //	ウィンドウサイズ
    cbuff.windowSize = DirectX::SimpleMath::Vector2(static_cast<float>(UIManager::WINDOW_SIZE_X), static_cast<float>(UIManager::WINDOW_SIZE_Y));
    cbuff.AlphaData = GetRenderRatio() - GetRenderRatioOffset();
    cbuff.isPressed = m_isKeyPressed;

    //	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
    context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::KeyUI), 0, NULL, &cbuff, 0, 0);
    shader->StartShader(ShaderManager::ShaderType::KeyUI);


    //	画像用サンプラーの登録
    ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
    context->PSSetSamplers(0, 1, sampler);
    //	半透明描画指定
    ID3D11BlendState* blendstate = states->NonPremultiplied();
    //	透明判定処理
    context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
    //	深度バッファに書き込み参照する
    context->OMSetDepthStencilState(states->DepthDefault(), 0);
    //	カリングは左周り
    context->RSSetState(states->CullNone());
    //	ピクセルシェーダにテクスチャを登録する。
    context->PSSetShaderResources(0, 1, GetTexture());
    //	インプットレイアウトの登録
    context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::KeyUI));

    //	板ポリゴンを描画
    auto& batch = GetBatch();
    batch.Begin();
    batch.Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
    batch.End();

    //	シェーダの登録を解除しておく
    shader->EndShader();

}


