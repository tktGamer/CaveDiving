#include "pch.h"
#include "Game/Message/Messenger.h"
#include "Game/Object/GameObject.h"

// s_messengerを初期化する
std::unique_ptr<Messenger> Messenger::s_messenger = nullptr;

// コンストラクタ
Messenger::Messenger()
{
}

// Messengerクラスのインスタンスを取得する
Messenger* Messenger::GetInstance()
{
	// Messengerクラスのインスタンス生成されていない場合
	if (s_messenger == nullptr)
	{
		// Messengerクラスのインスタンスを生成する
		s_messenger = std::unique_ptr<Messenger>(new Messenger());
	}
	// Messengerクラスのインスタンスを返す
	return s_messenger.get();
}

// インスタンスを破棄する
void Messenger::DestroyInstance()
{ 
	// Messengerクラスのインスタンスをリセットする
	s_messenger.reset();
}

// オブジェクトを登録する
void Messenger::Register(int objectID, GameObject* object)
{
	// オブジェクトIDとオブジェクトを登録する
	m_objects.emplace(objectID, object);
}

// オブジェクトの登録を解除する
void Messenger::UnRegister(int objectID)
{
	// オブジェクトIDが存在する場合にのみ削除する
	m_objects.erase(objectID);
}

// オブジェクトにメッセージを送信する
void Messenger::Notify(int objectID, Message::MessageID messageID)
{
	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);
	// メッセージを送信するオブジェクトが見つかった場合
	if (it != m_objects.end())
	{
		// 送信するオブジェクトのメッセージハンドラを呼び出す
		it->second->OnMessegeAccepted(messageID);
	}
}

// オブジェクトを取得する
GameObject* Messenger::GetObject(int objectID)
{
	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);
	// メッセージを送信するオブジェクトが見つかった場合
	if (it != m_objects.end())
	{
		// オブジェクトを取得する
		return it->second;
	}
	return nullptr;
}