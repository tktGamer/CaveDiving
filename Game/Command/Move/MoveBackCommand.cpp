/**
 * @file   MoveBackCommand.cpp
 *
 * @brief  後ろ移動コマンドに関するソースファイル
 *
 * @author 制作者名　福地貴翔　
 *
 * @date   日付　2026/03/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "MoveBackCommand.h"
#include "Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */

MoveBackCommand::MoveBackCommand()
{
}

/**
 * @brief デストラクタ
 */
MoveBackCommand::~MoveBackCommand()
{
}

/**
 * @brief コマンド実行
 *
 * @param[in] objectID  コマンドを送るオブジェクトの番号
 *
 * @return なし
 */
void MoveBackCommand::Execute(const int& objectID)
{
	//メッセンジャー
	Messenger* messenger = Messenger::GetInstance();
	//移動キーが押されたら移動状態へ遷移
	messenger->Notify(objectID, Message::MOVING);
	//後ろ方向
	messenger->Notify(objectID, Message::MOVE_BACK);
}



