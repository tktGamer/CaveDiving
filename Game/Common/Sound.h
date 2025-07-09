#pragma once

// ヘッダファイルの読み込み ===================================================
#include"pch.h"

// クラスの定義 ===============================================================
/**
  * @brief リソースの管理
  */
class Sound
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundSource;
	DirectX::SoundEffect* m_pSoundEffect;

	float m_volume;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Sound(DirectX::SoundEffect* pSoundEffect);

	// デストラクタ
	~Sound();


// 操作
public:
	// 再生
	void Play(bool isLoop);
	//停止
	void Stop();
// 取得/設定
public:
	// 音量設定
	void SetVolume(float volume=1.0f);
// 内部実装
private:
	// インスタンスの作成
	bool CreateInstance();
	// 音量変更
	void ChangeVolume();
};

