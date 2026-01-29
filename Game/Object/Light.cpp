/**
 * @file   Light.cpp
 *
 * @brief  ライトに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/25
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
	:
	GameObject{Tag::ObjectType::Light,parent,initialPosition,initialAngle},
	m_isOn{},
	m_color{DirectX::Colors::White},
	m_messageID{}
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
	//ライト情報の更新
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

/**
 * @brief メッセージを取得する
 *
 * @param[in] messageID　メッセージID
 *
 * @return なし
 */
void Light::OnMessegeAccepted(Message::MessageID messageID)
{
	messageID;
}

/**
 * @brief 衝突応答分岐
 *
 * @param[in] other　衝突相手のオブジェクトポインタ
 *
 * @return なし
 */
void Light::CollisionResponce(GameObject* other)
{
	other;
}

/**
 * @brief ライトを点ける
 *
 * @param[in] なし
 *
 * @return なし
 */
void Light::LightOn()
{
	m_isOn = true;
}

/**
 * @brief ライトが点いているか
 *
 * @param[in] なし
 *
 * @return ライトが点いているか
 */
bool Light::IsOn() const
{
	return m_isOn;
}

/**
 * @brief ライトのデータを取得
 *
 * @param[in] なし
 *
 * @return ライトのデータ
 */
const ModelShader::PointLightCB&  Light::GetLightData()
{
	return m_pointLight;
}

/**
 * @brief ライトのデータを設定
 *
 * @param[in] lightData　ライトのデータ
 *
 * @return なし
 */
void Light::SetLightData(const ModelShader::PointLightCB& lightData)
{
	m_pointLight = lightData;
}

/**
 * @brief ライトの色を設定
 *
 * @param[in] color　ライトの色
 *
 * @return なし
 */
void Light::SetLightColor(const DirectX::SimpleMath::Vector3& color)
{
	m_color = color;
}
