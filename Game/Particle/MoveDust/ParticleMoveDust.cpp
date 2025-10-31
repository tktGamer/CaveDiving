/**
 * @file   ParticleMoveDust.cpp
 *
 * @brief  敵消滅パーティクルに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/09/25
 */

 // ヘッダファイルの読み込み ===================================================

#include "pch.h"
#include "ParticleMoveDust.h"
#include"Game/Message/Messenger.h"

using namespace DirectX;

const static float ENDLESS = -100.0f;

/// <summary>
/// コンストラクタ
/// 引数は初期設定用の数値
/// </summary>
/// <param name="life">生存時間</param>
/// <param name="pos">座標</param>
/// <param name="velocity">速度</param>
/// <param name="accele">加速度</param>
/// <param name="startScale">初期サイズ</param>
/// <param name="endScale">最終サイズ</param>
/// <param name="startColor">初期色</param>
/// <param name="endColor">最終色</param>

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] life
 * @param[in] pos
 * @param[in] velocity
 * @param[in] accele
 * @param[in] startScale
 * @param[in] endScale
 * @param[in] startColor
 * @param[in] endColor
 */
ParticleMoveDust::ParticleMoveDust(
	float life,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 velocity,
	DirectX::SimpleMath::Vector3 accele,
	DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor)
	:Particle{ life,pos,velocity,accele,startScale,endScale,startColor,endColor }
{
}
/**
 * @brief デストラクタ
 */
ParticleMoveDust::~ParticleMoveDust()
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
bool ParticleMoveDust::Update()
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
	//	ライフが0未満なら自身を消してもらう
	if (life < 0.0f)
	{
		return false; //	
	}

	//	スケール。現在の生存時間から、大きさをLerpで算出する
	SetScele(SimpleMath::Vector3::Lerp(GetStartScale(), GetEndScale(), 1.0f - GetLife() / GetStartLife()));
	//	色。現在の生存時間から、色をLerpで算出する
	SetColor(SimpleMath::Color::Lerp(GetStartColor(), GetEndColor(), 1.0f - GetLife() / GetStartLife()));
	//	ライフを減らしていく
	life -= elapsedTime;
	SetLife(life);


	return true;
}

