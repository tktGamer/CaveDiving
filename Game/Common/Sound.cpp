// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Sound.h"

GameObject* Sound::m_pListenerObject = nullptr;

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] pSoundEffect　音データ
 */
Sound::Sound(DirectX::SoundEffect* pSoundEffect, bool is3DAudio)
	: m_soundSource{}
	, m_pSoundEffect{ pSoundEffect }
	, m_volume{ 1.0f }
	,m_is3DAudio{is3DAudio}
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

	if(m_is3DAudio)
	{
		DirectX::AudioListener listener;
		listener.SetPosition(m_pListenerObject->GetCurrentPosition());
		//listener.SetOrientationFromQuaternion(m_pListenerObject->GetCurrentQuaternion());
		DirectX::AudioEmitter emitter{};
		emitter.SetPosition(m_pListenerObject->GetCurrentPosition());
		
		m_soundSource->Apply3D(listener, emitter);
	}
	m_soundSource->Play(isLoop);
}


/**
 * @brief 再生していない場合再生する
 *
 * @param[in] isLoop ループ再生するかどうか
 *
 * @return なし
 */
void Sound::OncePlay(bool isLoop)
{
	//未再生の場合
	if (m_soundSource == nullptr)
	{
		

		//普通に再生
		Play(isLoop);
		return;
	}

	//再生中なら再生しない
	if (m_soundSource->GetState() == DirectX::SoundState::PLAYING) 
	{
		return;
	}

	Play(isLoop);
}


/**
 * @brief リスナー・エミッターの更新
 *
 * @param[in] listener
 * @param[in] emitter
 *
 * @return なし
 */
void Sound::Update(const DirectX::AudioListener& listener,const DirectX::AudioEmitter& emitter)
{
	m_listener = listener;
	m_emitter = emitter;
	
	m_soundSource->Apply3D(listener, emitter);
}

void Sound::Update(const DirectX::AudioEmitter& emitter)
{
	if(m_soundSource == nullptr)
	{
		return;
	}

	DirectX::AudioListener listener;
	listener.SetPosition(m_pListenerObject->GetCurrentPosition());
	listener.SetOrientationFromQuaternion(m_pListenerObject->GetCurrentQuaternion());

	m_soundSource->Apply3D(listener, emitter);
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

void Sound::SetListenerObject(GameObject* pListenerObject)
{
	Sound::m_pListenerObject = pListenerObject;
}


GameObject* Sound::GetListenerObject() const
{
	return m_pListenerObject;
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
 * @brief 再生状態の取得
 *
 * @param[in] なし
 *
 * @return 再生状態
 */const DirectX::SoundState& Sound::GetSoundState()
{

	return m_soundSource->GetState();
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
	if (m_is3DAudio) 
	{
		m_soundSource = m_pSoundEffect->CreateInstance(DirectX::SoundEffectInstance_Use3D);
	}
	else
	{
		m_soundSource = m_pSoundEffect->CreateInstance();
	}
	
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
