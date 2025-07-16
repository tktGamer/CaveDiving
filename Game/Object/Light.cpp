/**
 * @file   Light.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Light.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
Light::Light(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:GameObject{Tag::ObjectType::Light,parent,initialPosition,initialAngle}
	,m_graphics{Graphics::GetInstance()}
	,m_objectNumber{CountUpNumber()}
{
	Messenger::GetInstance()->Register(m_objectNumber, this);

	SetPosition(initialPosition);
	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(LightBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_lBuffer);

}



/**
 * @brief デストラクタ
 */
Light::~Light()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Light::Initialize()
{

	m_lBuff.LightPosition = GetPosition();
	m_lBuff.LightInvSqrRadius = 1.0f / (500 * 500); //ライトが届く距離（２乗の逆数）
	m_lBuff.LightColor = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	m_lBuff.LightIntensity = 1.0f;
	m_lBuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.01f, 0.025f, 0.0f); // デフォルトの減衰

}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Light::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_lBuff.LightPosition =currentPosition + GetPosition();
	m_lBuff.LightInvSqrRadius = 1.0f / (5 * 5); //ライトが届く距離（２乗の逆数）
	m_lBuff.LightColor = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	m_lBuff.LightIntensity = 3.0f;
	m_lBuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.1f, 0.006f, 0.0f); // デフォルトの減衰
	m_graphics->GetDeviceResources()->GetD3DDeviceContext()->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &m_lBuff, 0, 0);
}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Light::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();

	LightBuffer lbuff;
	lbuff.LightPosition = GetPosition();
	lbuff.LightInvSqrRadius = 1.0f / (500 * 500); //ライトが届く距離（２乗の逆数）
	lbuff.LightColor = DirectX::SimpleMath::Vector3(1.0f,1.0f,1.0f);
	lbuff.LightIntensity = 2.0f; 
	lbuff.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.01f, 0.025f, 0.0f); // デフォルトの減衰
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_lBuffer.Get(), 0, NULL, &lbuff, 0, 0);

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Light::Finalize()
{
}

void Light::OnMessegeAccepted(Message::MessageID messageID)
{
}

int Light::GetObjectNumber()
{
	return m_objectNumber;
}

ID3D11Buffer* Light::GetLightBuffer() const
{
	return m_lBuffer.Get();
}
