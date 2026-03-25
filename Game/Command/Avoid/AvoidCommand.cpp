/**
 * @file   AvoidCommand.cpp
 *
 * @brief  回避コマンドに関するソースファイル
 *
 * @author 制作者名　福地貴翔　
 *
 * @date   日付　2026/03/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "AvoidCommand.h"
#include "Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */

AvoidCommand::AvoidCommand()
{
}

/**
 * @brief デストラクタ
 */
AvoidCommand::~AvoidCommand()
{
}

/**
 * @brief コマンド実行
 *
 * @param[in] objectID  コマンドを送るオブジェクトの番号
 *
 * @return なし
 */
void AvoidCommand::Execute(const int& objectID)
{
	//メッセンジャー
	Messenger* messenger = Messenger::GetInstance();
	//回避状態へ遷移
	messenger->Notify(objectID, Message::AVOIDANCE);
}



