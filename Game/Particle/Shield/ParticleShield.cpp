/**
 * @file   ParticleShield.cpp
 *
 * @brief  敵消滅パーティクルに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/12/25
 */

 // ヘッダファイルの読み込み ===================================================

#include "pch.h"
#include "ParticleShield.h"
#include"Game/Message/Messenger.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
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
	float life,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 velocity,
	DirectX::SimpleMath::Vector3 accele,
	DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor)
	:Particle{ life,pos,velocity,accele,startScale,endScale,startColor,endColor }
{
	//	生存時間が経過した後の時間（消滅までの時間）を初期化
	m_afterLife = life * 0.2f;
	m_afterColor = endColor;
	m_afterColor.w = 0.0f;
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
	m_angle += 180.0f * elapsedTime;

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
	//if (life < 0.0f)
	//{
	//	if (life+m_afterLife < 0.0f) 
	//	{
	//		return false; //	生存時間が経過した後の時間も0未満なら、falseを返す
	//	}
	//	
	//	DirectX::SimpleMath::Color nowColor = GetNowColor();

	//	//最終的に透明になる
	//	nowColor.A(DirectX::SimpleMath::Color::Lerp(GetStartColor(), m_afterColor, 1.0f - (life + m_afterLife) / m_afterLife).w);

	//	SetColor(nowColor);
	//	life -= elapsedTime; //	生存時間が経過した後の時間を減らしていく
	//	SetLife(life);
	//	return true; //	生存時間が経過した後の時間はあるので、trueを返す
	//}

	//	スケール。現在の生存時間から、大きさをLerpで算出する
	SetScele(DirectX::SimpleMath::Vector3::Lerp(GetStartScale(), GetEndScale(), 1.0f - GetLife() / GetStartLife()));
	//	色。現在の生存時間から、色をLerpで算出する
	SetColor(DirectX::SimpleMath::Color::Lerp(GetStartColor(), GetEndColor(), 1.0f - GetLife() / GetStartLife()));
	//	ライフを減らしていく
	life -= elapsedTime;
	SetLife(life);

	return true;
}

