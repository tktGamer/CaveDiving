/**
 * @file   Messenger.h
 *
 * @brief  メッセンジャーに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/18
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
class Light;
// クラスの定義 ===============================================================
/**
  * @brief メッセンジャー
  */
class Messenger
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
// 取得・設定
public:
	// オブジェクトを取得する
	GameObject* GetObject(int objectID);
	//　ライトの配列を取得する
	const std::vector<Light*>& GetLights() const { return m_lights; };
	// 経過時間を取得する
	float GetElapsedTime() const { return m_elapsedTime; }
	// 経過時間を設定する
	void SetElapsedTime(const float& elapsedTime) { m_elapsedTime = elapsedTime; }
	//操作するオブジェクトを取得する
	const int& GetOperateObjectID() const { return m_operateObjectID; };
	//操作するオブジェクトを設定する
	void SetOperateObject(const int& objectID) { m_operateObjectID = objectID; };
	//プレイヤーオブジェクトIDを取得
	const int& GetPlayerObjectID() const { return m_playerObjectID; };
	//アウトラインのオン・オフを取得する
	const bool& IsOutLineActive() const { return m_outlineActive; };
	//アウトラインのオン・オフを設定する
	void SetOutLineActive(const bool& isActive) { m_outlineActive = isActive; };
//デストラクタ
	~Messenger();
//操作
	// Messengerクラスのインスタンスを取得する
	static Messenger* GetInstance();
	// Messengerクラスのインスタンスを破棄する
	static void DestroyInstance();
	// メッセージを送信する
	void Notify(int objectID, Message::MessageID message);
	// オブジェクトを登録する
	void Register(int objectID, GameObject* object);
	// オブジェクトの登録を解除する
	void UnRegister(int objectID);
	//ライト登録
	void RegisterLight(Light* light);
	//ライト解除
	void UnRegisterLight();
//コンストラクタ
private:
	// コンストラクタ
	Messenger();
	// コピー・ムーブ禁止
	Messenger(const Messenger&) = delete;
	Messenger& operator=(const Messenger&) = delete;
	Messenger(Messenger&&) = delete;
	Messenger& operator=(Messenger&&) = delete;
// データメンバの宣言 -----------------------------------------------
private:
	// メッセンジャーインスタンス
	static std::unique_ptr<Messenger> s_messenger;
	// オブジェクトIDとオブジェクトマッピング
	std::unordered_map<int, GameObject*> m_objects;
	//ライト配列
	std::vector<Light*> m_lights;
	// 経過時間
	float m_elapsedTime = 0.0f;
	//操作オブジェクトID
	int m_operateObjectID;
	//プレイヤーオブジェクトID
	int m_playerObjectID;
	//アウトライン有無
	bool m_outlineActive = false;
};

#endif		// MESSENGER_DEFINED

