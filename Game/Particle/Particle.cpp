//--------------------------------------------------------------------------------------
// File: Particle.cpp
//
// パーティクルクラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Particle.h"




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
Particle::Particle(float life,
	DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity, 
	DirectX::SimpleMath::Vector3 accele, DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor)
{
	//	与えられた生存時間（s）を取得
	m_startLife =
		m_life = life;
	//	初期位置を取得
	m_position = pos;
	//	移動ベクトルを取得
	m_velocity = velocity;
	//	加速度ベクトルを取得
	m_accele = accele;

	//	初めのサイズを取得
	m_startScale =
		m_nowScale = startScale;
	//	終了のサイズを取得
	m_endScale = endScale;


	//	初めの色を取得
	m_startColor =
		m_nowColor = startColor;
	//	終了の色を取得
	m_endColor = endColor;

}

/**
 * @brief デストラクタ
 */
Particle::~Particle()
{
}



/**
 * @brief ビルボード作成
 *
 * @param[in] eye　　カメラの位置
 * @param[in] up　　上ベクトル
 *
 * @return なし
 */
void Particle::CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	m_billboard =
		DirectX::SimpleMath::Matrix::CreateBillboard(m_position, eye - m_position, up);

	//	回転情報を設定する
	DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::Identity;
	//	180度逆を向いているので、補正するための情報を入れる
	rot._11 = -1;
	rot._33 = -1;

	m_billboard = rot * m_billboard;
}


void Particle::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_position = pos;
}
const DirectX::SimpleMath::Vector3 Particle::GetPosition() const
{
	return m_position;
}
void Particle::SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
{
	m_velocity = velocity;
}
const DirectX::SimpleMath::Vector3 Particle::GetVelocity() const
{
	return m_velocity;
}

void Particle::SetAccele(const DirectX::SimpleMath::Vector3& accele)
{
	m_accele = accele;
}

const DirectX::SimpleMath::Vector3 Particle::GetAccele() const
{
	return m_accele;
}

void Particle::SetScele(const DirectX::SimpleMath::Vector3& scale)
{
	m_nowScale = scale;
}

const DirectX::SimpleMath::Vector3 Particle::GetNowScale() const
{
	return m_nowScale;
}

const DirectX::SimpleMath::Vector3 Particle::GetStartScale() const
{
	return m_startScale;
}

const DirectX::SimpleMath::Vector3 Particle::GetEndScale() const
{
	return m_endScale;
}

void Particle::SetLife(const float& life)
{
	m_life = life;
}

const float Particle::GetLife() const
{
	return m_life;
}

const float Particle::GetStartLife() const
{
	return m_startLife;
}

void Particle::SetColor(const DirectX::SimpleMath::Color& color)
{
	m_nowColor = color;
}

const DirectX::SimpleMath::Color Particle::GetNowColor() const
{
	return m_nowColor;
}

const DirectX::SimpleMath::Color Particle::GetStartColor() const
{
	return m_startColor;
}

const DirectX::SimpleMath::Color Particle::GetEndColor() const
{
	return m_endColor;
}

const DirectX::SimpleMath::Matrix& Particle::GetBillBoard()
{
	return m_billboard;
}

