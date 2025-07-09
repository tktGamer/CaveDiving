#pragma once
#ifndef MESSENGER_DEFINED
#define MESSENGER_DEFINED
#include "Game/Message/Message.h"
#include <unordered_map>

class GameObject;

// Messengerクラス
class Messenger
{
public:
	// オブジェクトを取得する
	GameObject* GetObject(int objectID);
	// 経過時間を取得する
	float GetElapsedTime() const { return m_elapsedTime; }
	// 経過時間を設定する
	void SetElapsedTime(const float& elapsedTime) { m_elapsedTime = elapsedTime; }

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
	void Notify(int objectID, Message::MessageID);

private:
	// コピー・ムーブ禁止
	Messenger(const Messenger&) = delete;
	Messenger& operator=(const Messenger&) = delete;
	Messenger(Messenger&&) = delete;
	Messenger& operator=(Messenger&&) = delete;
	// コンストラクタ
	Messenger();

private:
	// メッセンジャーインスタンス
	static std::unique_ptr<Messenger> s_messenger;
	// オブジェクトIDとオブジェクトマッピング
	std::unordered_map<int, GameObject*> m_objects;
	// 経過時間
	float m_elapsedTime;

};

#endif		// MESSENGER_DEFINED

