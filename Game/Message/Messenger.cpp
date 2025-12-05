/**
 * @file   Messenger.cpp
 *
 * @brief  メッセンジャーに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/25
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Game/Message/Messenger.h"
#include "Game/Object/GameObject.h"

// s_messengerを初期化する
std::unique_ptr<Messenger> Messenger::s_messenger = nullptr;

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]なし
 */
Messenger::Messenger()
	:m_elapsedTime{0.0f}
	,m_outlineActive{}
{
}

/**
 * @brief インスタンスの取得
 *
 * @param[in] なし
 */
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



/**
 * @brief インスタンスを破棄
 *
 * @param[in] なし
 *
 * @return なし
 */
void Messenger::DestroyInstance()
{ 
	// Messengerクラスのインスタンスをリセットする
	s_messenger.reset();
}



/**
 * @brief オブジェクトを登録する
 *
 * @param[in] objectID 登録ID
 * @param[in] object   登録するオブジェクトのポインタ
 *
 * @return なし
 */
void Messenger::Register(int objectID, GameObject* object)
{
	// オブジェクトIDとオブジェクトを登録する
	m_objects.emplace(objectID, object);
}

/**
 * @brief オブジェクトの登録を破棄する
 *
 * @param[in] objectID 登録ID
 *
 * @return なし
 */
void Messenger::UnRegister(int objectID)
{
	// オブジェクトIDが存在する場合にのみ削除する
	m_objects.erase(objectID);
}

/**
 * @brief オブジェクトにメッセージを送信
 *
 * @param[in] objectID   登録ID
 * @param[in] messageID　送信するメッセージ
 *
 * @return なし
 */
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

/**
 * @brief 登録されているオブジェクトを取得する
 *
 * @param[in] objectID   登録ID
 *
 * @return なし
 */
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