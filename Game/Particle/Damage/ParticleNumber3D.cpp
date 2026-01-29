/**
 * @file   ParticleNumber3D.cpp
 *
 * @brief  3D空間上の数字に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/26
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ParticleNumber3D.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Shader/Shader.h"
#include"Game/Message/Messenger.h"
 // メンバ関数の定義 ===========================================================
 /**
  * @brief コンストラクタ
  *
  * @param[in] life　　　　生存時間
  * @param[in] pos　　　　 座標
  * @param[in] velocity　　速度
  * @param[in] accele　　　加速度
  * @param[in] startScale　初期サイズ
  * @param[in] endScale　　最終サイズ
  * @param[in] startColor　初期色
  * @param[in] endColor　　最終色
  * @param[in] num　　     表示する数字
  */
ParticleNumber3D::ParticleNumber3D(
	float life,
	const DirectX::SimpleMath::Vector3& pos,
	const DirectX::SimpleMath::Vector3& velocity,
	const DirectX::SimpleMath::Vector3& accele,
	const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
	const DirectX::SimpleMath::Color& startColor,const DirectX::SimpleMath::Color& endColor,
	int num)
	:
	Particle{ life,pos,velocity,accele,startScale,endScale,startColor,endColor },
	m_number{ num }
{
}

/**
 * @brief デストラクタ
 */
ParticleNumber3D::~ParticleNumber3D()
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
bool ParticleNumber3D::Update()
{
	//	処理に使う秒速計(1秒で1.0f)を取得する。
	float elapsedTime = Messenger::GetInstance()->GetElapsedTime();


	//	速度の計算。経過時間と加速度を掛け算して足すことで、加速度を考慮して移動速度を変化させていく
	DirectX::SimpleMath::Vector3 velocity = GetVelocity();
	velocity += GetAccele() * elapsedTime;
	SetVelocity(velocity);
	//	座標の計算。経過時間と移動速度から、現在の座標を算出する
	DirectX::SimpleMath::Vector3 position = GetPosition();

	position += GetVelocity() * elapsedTime;
	SetPosition(position);


	float life = GetLife();
	//ライフが0未満なら自身を消してもらう
	if (life < 0.0f)
	{
		return false; //	生存時間が経過した後の時間も0未満なら、falseを返す
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