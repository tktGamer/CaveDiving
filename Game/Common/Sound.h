/**
 * @file   Sound.h
 *
 * @brief  音に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/10/22
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


// データメンバの宣言 -----------------------------------------------
private:
	//リスナー
	static GameObject* m_pListenerObject;
	//サウンドインスタンス
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundSource;
	DirectX::SoundEffect* m_pSoundEffect;

	bool m_is3DAudio;
	DirectX::AudioEmitter m_emitter;
	DirectX::AudioListener m_listener;
	

	float m_volume;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Sound(DirectX::SoundEffect* pSoundEffect,bool is3DAudio = false);

	// デストラクタ
	~Sound();


// 操作
public:

	// 再生
	void Play(bool isLoop);
	//重ねて再生しない
	void OncePlay(bool isLoop);

	//エミッター・リスナーの更新
	void Update(const DirectX::AudioListener& listener, const DirectX::AudioEmitter& emitter);
	void Update(const DirectX::AudioEmitter& emitter);

	//停止
	void Stop();
// 取得/設定
public:
	//リスナーオブジェクトの設定
	static void SetListenerObject(GameObject* pListenerObject);
	GameObject* GetListenerObject() const;

	// 音量設定
	void SetVolume(float volume=1.0f);

	//再生状態の取得
	const DirectX::SoundState& GetSoundState();
// 内部実装
private:
	// インスタンスの作成
	bool CreateInstance();
	// 音量変更
	void ChangeVolume();
};

