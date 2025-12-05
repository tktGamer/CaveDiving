/**
 * @file   Messenger.h
 *
 * @brief  メッセンジャーに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef MESSENGER_DEFINED
#define MESSENGER_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Message/Message.h"
#include <unordered_map>

// クラスの宣言 ===============================================================
class GameObject;

// クラスの定義 ===============================================================
/**
  * @brief メッセンジャー
  */
class Messenger
{
private:
	// メッセンジャーインスタンス
	static std::unique_ptr<Messenger> s_messenger;
	// オブジェクトIDとオブジェクトマッピング
	std::unordered_map<int, GameObject*> m_objects;
	// 経過時間
	float m_elapsedTime;

	//強化の適用するか
	bool m_isApplyPowerUp = false;

	//アウトライン有無
	bool m_outlineActive;
//コンストラクタ・デストラクタ
private:
	// コピー・ムーブ禁止
	Messenger(const Messenger&) = delete;
	Messenger& operator=(const Messenger&) = delete;
	Messenger(Messenger&&) = delete;
	Messenger& operator=(Messenger&&) = delete;
	// コンストラクタ
	Messenger();
//操作
public:
	// Messengerクラスのインスタンスを取得する
	static Messenger* GetInstance();
	// Messengerクラスのインスタンスを破棄する
	static void DestroyInstance();
	// オブジェクトを登録する
	void Register(int objectID, GameObject* object);
	// オブジェクトの登録を解除する
	void UnRegister(int objectID);
	// メッセージを送信する
	void Notify(int objectID, Message::MessageID message);
// 取得・設定
public:
	// オブジェクトを取得する
	GameObject* GetObject(int objectID);
	// 経過時間を取得する
	float GetElapsedTime() const { return m_elapsedTime; }
	// 経過時間を設定する
	void SetElapsedTime(const float& elapsedTime) { m_elapsedTime = elapsedTime; }

	//アウトラインのオン・オフを取得する
	const bool& IsOutLineActive() const { return m_outlineActive; };
	void SetOutLineActive(const bool& isActive) { m_outlineActive = isActive; };
};

#endif		// MESSENGER_DEFINED

