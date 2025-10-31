/**
 * @file   Particle.cpp
 *
 * @brief  パーティクルに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2025/10/22
 */

 // ヘッダファイルの読み込み ===================================================
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
 * @brief 座標の設定
 *
 * @param[in] pos　　座標
 *
 * @return なし
 */
void Particle::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_position = pos;
}

/**
 * @brief 座標の取得
 *
 * @param[in] なし
 *
 * @return 座標
 */
const DirectX::SimpleMath::Vector3 Particle::GetPosition() const
{
	return m_position;
}

/**
 * @brief 速度の設定
 *
 * @param[in] velocity　　速度
 *
 * @return なし
 */
void Particle::SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
{
	m_velocity = velocity;
}

/**
 * @brief 速度の取得
 *
 * @param[in] なし
 *
 * @return 速度
 */
const DirectX::SimpleMath::Vector3 Particle::GetVelocity() const
{
	return m_velocity;
}


/**
 * @brief 加速度の設定
 *
 * @param[in] accele　　加速度
 *
 * @return なし
 */
void Particle::SetAccele(const DirectX::SimpleMath::Vector3& accele)
{
	m_accele = accele;
}

/**
 * @brief 加速度の取得
 *
 * @param[in] なし
 *
 * @return 加速度
 */
const DirectX::SimpleMath::Vector3 Particle::GetAccele() const
{
	return m_accele;
}

/**
 * @brief 現在の大きさの設定
 *
 * @param[in] scale　　大きさ
 *
 * @return なし
 */
void Particle::SetScele(const DirectX::SimpleMath::Vector3& scale)
{
	m_nowScale = scale;
}

/**
 * @brief 現在の大きさの取得
 *
 * @param[in] なし
 *
 * @return 大きさ
 */
const DirectX::SimpleMath::Vector3 Particle::GetNowScale() const
{
	return m_nowScale;
}

/**
 * @brief 初期の大きさの取得
 *
 * @param[in] なし
 *
 * @return 大きさ
 */
const DirectX::SimpleMath::Vector3 Particle::GetStartScale() const
{
	return m_startScale;
}

/**
 * @brief 最終の大きさの取得
 *
 * @param[in] なし
 *
 * @return 大きさ
 */
const DirectX::SimpleMath::Vector3 Particle::GetEndScale() const
{
	return m_endScale;
}

/**
 * @brief 生存時間の設定
 *
 * @param[in] life　　生存時間
 *
 * @return なし
 */
void Particle::SetLife(const float& life)
{
	m_life = life;
}

/**
 * @brief 生存時間の取得
 *
 * @param[in] なし
 *
 * @return 生存時間
 */
const float Particle::GetLife() const
{
	return m_life;
}

/**
 * @brief 初期生存時間の取得
 *
 * @param[in] なし
 *
 * @return 初期生存時間
 */
const float Particle::GetStartLife() const
{
	return m_startLife;
}

/**
 * @brief 現在の色の設定
 *
 * @param[in] color　　色
 *
 * @return なし
 */
void Particle::SetColor(const DirectX::SimpleMath::Color& color)
{
	m_nowColor = color;
}

/**
 * @brief 現在の色の取得
 *
 * @param[in] なし
 *
 * @return 色
 */
const DirectX::SimpleMath::Color Particle::GetNowColor() const
{
	return m_nowColor;
}

/**
 * @brief 初期の色の取得
 *
 * @param[in] なし
 *
 * @return 色
 */
const DirectX::SimpleMath::Color Particle::GetStartColor() const
{
	return m_startColor;
}

/**
 * @brief 最終の色の取得
 *
 * @param[in] なし
 *
 * @return 色
 */
const DirectX::SimpleMath::Color Particle::GetEndColor() const
{
	return m_endColor;
}


