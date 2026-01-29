/**
 * @file   Sound.h
 *
 * @brief  音に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"pch.h"
#include"x3daudio.h"
#include "Game/Object/GameObject.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 音
  */
class Sound
{
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr float VOLUME_MAX = 1.0f;

// メンバ関数の宣言 -------------------------------------------------
// 取得/設定
public:
	// 音量設定
	void SetVolume(float volume=1.0f);
	//再生状態の取得
	const DirectX::SoundState& GetSoundState();
// コンストラクタ/デストラクタ
	// コンストラクタ
	Sound(DirectX::SoundEffect* pSoundEffect);
	// デストラクタ
	~Sound();
// 操作
	// 再生
	void Play(bool isLoop);
	//重ねて再生しない
	void OncePlay(bool isLoop);
	//停止
	void Stop();
// 内部実装
private:
	// インスタンスの作成
	bool CreateInstance();
	// 音量変更
	void ChangeVolume();
// データメンバの宣言 -----------------------------------------------
private:
	//サウンドインスタンス
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundSource;
	DirectX::SoundEffect* m_pSoundEffect;
	//音量
	float m_volume;

};

