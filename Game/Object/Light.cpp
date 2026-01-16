/**
 * @file   Light.cpp
 *
 * @brief  ライトに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/02
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Light.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] parent　		   親オブジェクト 
 * @param[in] initialPosition　初期座標 
 * @param[in] initialAngle　　 初期角度 
 */
Light::Light(const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{Tag::ObjectType::Light,parent,initialPosition,initialAngle}
	,m_isOn{}
	,m_color{DirectX::Colors::White}
{
	//メッセンジャーに登録
	Messenger::GetInstance()->Register(GetObjectNumber(), this);

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
void Light::Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//位置の更新
	SetCurrentPosition(currentPosition + GetPosition());
	//角度の更新
	SetCurrentAngle(GetQuaternion() * currentAngle );




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


const ModelShader::PointLightCB&  Light::GetLightData()
{
	return m_pointLight;
}

void Light::SetLightData(const ModelShader::PointLightCB& lightData)
{
	m_pointLight = lightData;
}

void Light::SetLightColor(const DirectX::SimpleMath::Vector3& color)
{
	m_color = color;
}
