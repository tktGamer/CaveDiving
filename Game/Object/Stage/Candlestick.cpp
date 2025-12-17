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
#include"Game/Shader/ShaderManager.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
CandleStick::CandleStick(const ModelShader::PointLightCB& lightData, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{ Tag::ObjectType::Light,parent,initialPosition,initialAngle }
	, m_graphics{ Graphics::GetInstance() }
	, m_box{ GetPosition(),DirectX::SimpleMath::Vector3{1.3f,1.3f,1.3f} }
	, m_isOn{}
	,m_color{}
	,m_messageID{}
	, m_display{ Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice(),
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext() }

{
	Messenger::GetInstance()->Register(GetObjectNumber(), this);
	SetModel(ResourceManager::GetInstance()->RequestModel("rock.sdkmesh"));
	SetTexture(ResourceManager::GetInstance()->RequestTexture("rock.png"));
	SetShape(&m_box);

	m_light = std::make_unique<Light>(nullptr, m_initialPosition, m_initialAngle);
	m_light->Initialize();

	m_light->SetLightData(lightData);

	Messenger::GetInstance()->RegisterLight(m_light.get());

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
void CandleStick::Initialize(bool isOnLight)
{
	//m_light = std::make_unique<Light>(nullptr, m_initialPosition,m_initialAngle);
	//m_light->Initialize();
	if (isOnLight) 
	{
		OnLight();
	}
	//m_light->LightOn();
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void CandleStick::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{

	m_currentAngle =m_initialAngle* GetQuaternion() * currentAngle;
	m_currentPosition = m_initialPosition + GetPosition() + currentPosition;

	m_light->Update(m_currentPosition, m_currentAngle);
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


	Graphics* graphics = Graphics::GetInstance();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	CandleStick::ConstBuffer cbuff;
	cbuff.matWorld = TKTLib::GetWorldMatrix(GetCurrentPosition(), GetCurrentQuaternion(), GetScale()).Transpose();
	cbuff.matView = graphics->GetViewMatrix().Transpose();
	cbuff.matProj = graphics->GetProjectionMatrix().Transpose();
	cbuff.color = m_color;
	ShaderManager* shader = ShaderManager::GetInstance();
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(shader->GetCBuffer(ShaderManager::Rock_Model), 0, NULL, &cbuff, 0, 0);

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
			ShaderManager::GetInstance()->StartShader(ShaderManager::Rock_Model);

			//auto ps = shader->GetRockPS();

			//auto constBuffer = shader->GetCBuffer(ShaderManager::ShaderType::Rock_Model);
			////	シェーダーにバッファを渡す
			//ID3D11Buffer* cb[1] = { constBuffer };

			//context->PSSetConstantBuffers(0, 1, cb);
			//context->PSSetShader(ps, nullptr, 0);


			//頂点情報を設定
			context->IASetInputLayout(shader->GetInputLayout(ShaderManager::ShaderType::Rock_Model));

		});
	ShaderManager::GetInstance()->EndShader();

	//m_box.AddDisplayCollision(&m_display);
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
	switch (other->GetObjectType()) 
	{
	case Tag::ObjectType::Weapon:
	{
		OnLight();
		break;
	}

	}
}

void CandleStick::OnLight()
{
	//明かりを点ける
	m_light->LightOn();
	m_color = { 1.0f,1.0f,1.0f,1.0f };

}

bool CandleStick::IsOnLight()
{
	return m_light->IsOn();
}
