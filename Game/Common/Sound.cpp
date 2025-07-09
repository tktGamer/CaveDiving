// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Sound.h"


// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pSoundEffect
 */
Sound::Sound(DirectX::SoundEffect* pSoundEffect)
	: m_soundSource{}
	, m_pSoundEffect{ pSoundEffect }
	, m_volume{ 1.0f }
{
}
/**
 * @brief デストラクタ
 */
Sound::~Sound()
{
}

/**
 * @brief 再生
 *
 * @param[in] isLoop ループ再生するかどうか
 *
 * @return なし
 */
void Sound::Play(bool isLoop)
{
	if (CreateInstance() == false)
	{
		return;
	}
	ChangeVolume();
	m_soundSource->Play(isLoop);
}

/**
 * @brief 停止
 * 
 * @param[in] なし
 * 
 * @return なし
 */
void Sound::Stop()
{
	CreateInstance();
	m_soundSource->Stop();
}

/**
 * @brief 音量設定
 *
 * @param[in] volume 音量 0.0f～1.0f
 *
 * @return なし
 */
void Sound::SetVolume(float volume)
{
	if (volume < 0.0f)
	{
		volume = 0.0f;
	}
	else if (volume > 1.0f)
	{
		volume = 1.0f;
	}
	m_volume = volume;
}

/**
 * @brief インスタンスの作成
 *
 * @param[in] なし
 *
 * @return なし
 */
bool Sound::CreateInstance()
{
	if (m_pSoundEffect == nullptr)
	{
		return false;
	}
	m_soundSource = m_pSoundEffect->CreateInstance();
	return true;
}

/**
 * @brief 音量変更
 *
 * @param[in] なし
 *
 * @return なし
 */
void Sound::ChangeVolume()
{
	m_soundSource->SetVolume(m_volume);
}
