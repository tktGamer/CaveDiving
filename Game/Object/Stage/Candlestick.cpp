/**
 * @file   CandleStick.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "CandleStick.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
CandleStick::CandleStick(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{ Tag::ObjectType::Light,parent,initialPosition,initialAngle }
	, m_graphics{ Graphics::GetInstance() }
	, m_box{ GetPosition(),DirectX::SimpleMath::Vector3{2.0f,2.0f,2.0f} }
	, m_isOn{}
	, m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	Messenger::GetInstance()->Register(GetObjectNumber(), this);
	SetModel(ResourceManager::GetInstance()->RequestModel("candle.sdkmesh"));
	SetTexture(ResourceManager::GetInstance()->RequestTexture("candle.png"));
	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(CandleStickBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_lBuffer);

}



/**
 * @brief デストラクタ
 */
CandleStick::~CandleStick()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CandleStick::Initialize()
{
	
	//m_lBuff.CandleStickPosition = GetPosition();
	//m_lBuff.CandleStickInvSqrRadius = 1.0f / (500 * 500); //ライトが届く距離（２乗の逆数）
	//m_lBuff.CandleStickColor = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	//m_lBuff.CandleStickIntensity = 1.0f;
	//m_lBuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.01f, 0.025f, 0.0f); // デフォルトの減衰

	m_light = std::make_unique<Light>(nullptr, m_initialPosition,m_initialAngle);
	m_light->Initialize();
	m_light->LightOn();
	Shader::GetInstance()->RegisterLight(m_light.get());
}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CandleStick::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//m_lBuff.CandleStickPosition =currentPosition + GetPosition();
	//m_lBuff.CandleStickInvSqrRadius = 1.0f / (5 * 5); //ライトが届く距離（２乗の逆数）
	//m_lBuff.CandleStickColor = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	//m_lBuff.CandleStickIntensity = 3.0f;
	//m_lBuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.1f, 0.006f, 0.0f); // デフォルトの減衰
	//m_graphics->GetDeviceResources()->GetD3DDeviceContext()->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &m_lBuff, 0, 0);

	m_currentAngle =m_initialAngle* GetQuaternion() * currentAngle;
	m_currentPosition = m_initialPosition + GetPosition() + currentPosition;

	m_light->Update(elapsedTime, m_currentPosition, m_currentAngle);
	m_box.SetCenter(GetCurrentPosition());

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CandleStick::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();

	//CandleStickBuffer lbuff;
	//lbuff.CandleStickPosition = GetPosition();
	//lbuff.CandleStickInvSqrRadius = 1.0f / (500 * 500); //ライトが届く距離（２乗の逆数）
	//lbuff.CandleStickColor = DirectX::SimpleMath::Vector3(1.0f,1.0f,1.0f);
	//lbuff.CandleStickIntensity = 2.0f; 
	//lbuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.01f, 0.025f, 0.0f); // デフォルトの減衰
	////	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	//context->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &lbuff, 0, 0);

	Graphics* graphics = Graphics::GetInstance();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	CandleStick::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();

	Shader* shader = Shader::GetInstance();
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(Shader::Model), 0, NULL, &cbuff, 0, 0);

	GetModel()->Draw(context, *states, world, view, proj, false, [&]()
		{
			//	モデル表示をするための自作シェーダに関連する設定を行う


			//	画像用サンプラーの登録
			ID3D11SamplerState* sampler[1] = { states->PointWrap() };
			context->PSSetSamplers(0, 1, sampler);

			if (GetTexture() != nullptr)
			{
				//	読み込んだ画像をピクセルシェーダに伝える
				//	自作VSはt0を使っているため、
				//	t0がメインで使われていると勝手に想定。
				context->PSSetShaderResources(0, 1, GetTexture());
			}

			//	半透明描画指定
			ID3D11BlendState* blendstate = states->NonPremultiplied();

			//	透明判定処理
			context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

			//	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	カリングはなし
			context->RSSetState(states->CullClockwise());

			//シェーダーの設定
			Shader::GetInstance()->StartShader(Shader::Model, shader->GetCBuffer(Shader::Model));

			//頂点情報を設定
			context->IASetInputLayout(shader->GetInputLayout(Shader::Model));

		});
	Shader::GetInstance()->EndShader();

	m_box.AddDisplayCollision(&m_display);
	m_display.DrawCollision(Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), Graphics::GetInstance()->GetCommonStates()
		, Graphics::GetInstance()->GetViewMatrix(), Graphics::GetInstance()->GetProjectionMatrix());

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CandleStick::Finalize()
{
}

void CandleStick::OnMessegeAccepted(Message::MessageID messageID)
{
}

void CandleStick::CollisionResponce(GameObject* other)
{
}
