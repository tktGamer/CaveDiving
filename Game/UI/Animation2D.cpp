/**
 * @file   Animation2D.cpp
 *
 * @brief  2Dアニメーションに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Animation2D.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Shader/ShaderManager.h"
#include"Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Animation2D::Animation2D(const wchar_t* texturepath, const AnimationTexture& textureInfo, const float& animationTime, const bool& isLoop,
	const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale)
	: m_graphics{Graphics::GetInstance()}
	, m_pAnimation2DTexture{}
	, m_textureSize{}
	, m_anchor{UserInterface::ANCHOR::MIDDLE_CENTER}
	, m_windowHeight{ 0 }
	, m_windowWidth{ 0 }
	, m_scale{ scale }
	, m_position{ position }
	, m_renderRatio{ 1.0f }
	, m_renderRatioOffset{ 0.0f },
	m_textureInfo{textureInfo},
	m_animationTime{animationTime},
	m_loop{isLoop}

{
	m_pAnimation2DTexture = ResourceManager::GetInstance()->RequestTexture(texturepath);
	int textureSizeX, textureSizeY;
	ResourceManager::GetInstance()->GetTextureSize(texturepath, textureSizeX, textureSizeY);
	m_textureSize.x = textureSizeX;
	m_textureSize.y = textureSizeY;
	//一枚あたりの大きさ
	m_frameSize.x = m_textureSize.x / m_textureInfo.frameWidth;
	m_frameSize.y = m_textureSize.y / m_textureInfo.frameHeight;
	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_graphics->GetDeviceResources()->GetD3DDeviceContext());

}



/**
 * @brief デストラクタ
 */
Animation2D::~Animation2D()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Animation2D::Initialize()
{

}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Animation2D::Update()
{
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	m_currentTime += elapsedTime;
	if (IsFinish()) 
	{
		if (m_loop) 
		{
			m_currentTime = 0.0f;
		}
		else
		{
			m_currentTime = m_animationTime;
		}
	}
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Animation2D::Draw()
{
	ShaderManager* shader = ShaderManager::GetInstance();

	ID3D11DeviceContext1* context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	//	頂点情報
	//	Position.xy	:拡縮用スケール
	//	Position.z	:アンカータイプ(0～8)の整数で指定
	//	Color.xy　	:アンカー座標(ピクセル指定:1280 ×720)
	//	Color.zw	:画像サイズ
	//	Tex.xy		:x = 0, y = 0
	DirectX::VertexPositionColorTexture vertex[1] = {
		DirectX::VertexPositionColorTexture(
			 DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_anchor))
			,DirectX::SimpleMath::Vector4(m_position.x , m_position.y, m_frameSize.x, m_frameSize.y)
			,m_textureSize)
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	Animation2DShader::Animation2DCB cbuff;
	//	ウィンドウサイズ
	cbuff.windowSize = DirectX::SimpleMath::Vector2(static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight));
	cbuff.alphaData = m_renderRatio - m_renderRatioOffset;
	//アニメーション時間
	cbuff.animationTime = m_animationTime; 
	//経過時間
	cbuff.currentTime = m_currentTime;
	//総枚数
	cbuff.frameCount = m_textureInfo.frameCount;
	//幅の枚数
	cbuff.widthFrame = m_textureInfo.frameWidth;
	//縦の枚数
	cbuff.heightFrame = m_textureInfo.frameHeight;

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::ShaderType::Animation2D), 0, NULL, &cbuff, 0, 0);
	shader->StartShader(ShaderManager::ShaderType::Animation2D);


	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { Graphics::GetInstance()->GetCommonStates()->LinearWrap()};
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = Graphics::GetInstance()->GetCommonStates()->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(Graphics::GetInstance()->GetCommonStates()->DepthDefault(), 0);

	//	カリングは左周り
	context->RSSetState(Graphics::GetInstance()->GetCommonStates()->CullNone());


	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_pAnimation2DTexture);

	//	インプットレイアウトの登録
	context->IASetInputLayout(shader->GetInputLayout(ShaderManager::Animation2D));

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	shader->EndShader();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Animation2D::Finalize()
{

}

/**
 * @brief ウィンドウサイズ設定
 *
 * @param[in] windowSize ウィンドウサイズ
 *
 * @return なし
 */
void Animation2D::SetWindowSize(const DirectX::SimpleMath::Vector2& windowSize)
{
	m_windowWidth = windowSize.x;
	m_windowHeight = windowSize.y;
}


/**
 * @brief アニメーションが終了したか
 *
 * @param[in] なし
 *
 * @return なし
 */
bool Animation2D::IsFinish() const 
{
	return (m_currentTime >= m_animationTime);
}