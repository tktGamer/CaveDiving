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
Light::Light(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{Tag::ObjectType::Light,parent,initialPosition,initialAngle}
	,m_graphics{Graphics::GetInstance()}
	,m_isOn{}
	,m_color{DirectX::Colors::White}
{
	Messenger::GetInstance()->Register(GetObjectNumber(), this);

	SetPosition(initialPosition);

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
	m_currentAngle = m_initialAngle * GetQuaternion() * currentAngle;
	m_currentPosition = m_initialPosition + GetPosition() + currentPosition;



	m_pointLight.LightPosition = GetCurrentPosition();
	m_pointLight.LightInvSqrRadius = 1.0f / (5 * 5); //ライトが届く距離（２乗の逆数）
	m_pointLight.LightColor = m_color;
	m_pointLight.LightIntensity = 1.0f;
	m_pointLight.Attenuation = DirectX::SimpleMath::Vector4(1.0f, 0.1f, 0.006f, 0.0f); // デフォルトの減衰
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

void Light::CollisionResponce(GameObject* other)
{
}

void Light::LightOn()
{
	m_isOn = true;
}


bool Light::IsOn() const
{
	return m_isOn;
}

ID3D11Buffer* Light::GetLightBuffer() const
{
	return m_lBuffer.Get();
}

Shader::PointLight Light::GetLightData()
{
	return m_pointLight;
}

void Light::SetLightData(const Shader::PointLight& lightData)
{
	m_pointLight = lightData;
}

void Light::SetLightColor(const DirectX::SimpleMath::Vector3& color)
{
	m_color = color;
}
