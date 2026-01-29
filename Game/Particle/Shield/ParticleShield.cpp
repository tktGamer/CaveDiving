/**
 * @file   ParticleShield.cpp
 *
 * @brief  盾パーティクルに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/28
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleShield.h"
#include"Game/Message/Messenger.h"
#include"Game/Object/GameObject.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] centerObjectID 中心オブジェクトのID
 * @param[in] life　　　　生存時間
 * @param[in] pos 座標
 * @param[in] velocity 速度
 * @param[in] accele 加速度
 * @param[in] startScale 初期サイズ
 * @param[in] endScale 最終サイズ
 * @param[in] startColor 初期色
 * @param[in] endColor 最終色
 * 
 */
ParticleShield::ParticleShield(
	const int& centerObjectID,
	float life,
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& velocity,
	const DirectX::SimpleMath::Vector3& accele,
	const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
	const DirectX::SimpleMath::Color& startColor,const DirectX::SimpleMath::Color& endColor)
	:
	Particle{ life,pos,velocity,accele,startScale,endScale,startColor,endColor },
	m_centerObjectID{centerObjectID}
{
}
/**
 * @brief デストラクタ
 */
ParticleShield::~ParticleShield()
{
}

/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return true   生存中
 * @return false  死亡
 */
bool ParticleShield::Update()
{
	//	処理に使う秒速計(1秒で1.0f)を取得する。
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();
	m_angle += ROTATE_SPEED * elapsedTime;

	float angle = DirectX::XMConvertToRadians(m_angle); // 各オブジェクトの角度
	float addX = 2.0f * cos(angle); // X座標
	float addZ = 2.0f * sin(angle); // Z座標


	//	速度の計算。経過時間と加速度を掛け算して足すことで、加速度を考慮して移動速度を変化させていく
	DirectX::SimpleMath::Vector3 velocity = GetVelocity();
	velocity += GetAccele() * elapsedTime;
	SetVelocity(velocity);
	//	座標の計算。経過時間と移動速度から、現在の座標を算出する
	//DirectX::SimpleMath::Vector3 position = GetPosition();
	DirectX::SimpleMath::Vector3 position{addX,0.0f,addZ};

	position += GetVelocity() * elapsedTime;
	SetPosition(position);


	float life = GetLife();
	//	ライフが0未満なら自身を消してもらう
	if (life < 0.0f)
	{
		return false; //	生存時間が経過した後の時間はあるので、trueを返す
	}

	//	スケール。現在の生存時間から、大きさをLerpで算出する
	SetScele(DirectX::SimpleMath::Vector3::Lerp(GetStartScale(), GetEndScale(), 1.0f - GetLife() / GetStartLife()));
	//	色。現在の生存時間から、色をLerpで算出する
	SetColor(DirectX::SimpleMath::Color::Lerp(GetStartColor(), GetEndColor(), 1.0f - GetLife() / GetStartLife()));
	//	ライフを減らしていく
	life -= elapsedTime;
	SetLife(life);

	return true;
}


/**
 * @brief 中心位置
 *
 * @param[in] なし
 *
 * @return 中心位置
 */
const DirectX::SimpleMath::Vector3& ParticleShield::GetCenterPosition() const
{
	return Messenger::GetInstance()->GetObject(m_centerObjectID)->GetCurrentPosition();
}

