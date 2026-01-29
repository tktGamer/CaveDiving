/**
 * @file   IObserver.h
 *
 * @brief  オブザーバーのインターフェイスに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED
// ヘッダファイルの読み込み ===================================================
#include "Game/Message/Message.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief IObserverインターフェースを定義する
  */
class IObserver
{
// 操作
public:
	// メッセージを受け取る
	virtual void OnMessegeAccepted(Message::MessageID messageID) = 0;
};

#endif	// IOBSERVER_DEFINED
