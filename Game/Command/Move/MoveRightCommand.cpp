/**
 * @file   MoveRightCommand.cpp
 *
 * @brief  右移動コマンドに関するソースファイル
 *
 * @author 制作者名　福地貴翔　
 *
 * @date   日付　2026/03/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "MoveRightCommand.h"
#include "Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */

MoveRightCommand::MoveRightCommand()
{
}

/**
 * @brief デストラクタ
 */
MoveRightCommand::~MoveRightCommand()
{
}

/**
 * @brief コマンド実行
 *
 * @param[in] objectID  コマンドを送るオブジェクトの番号
 *
 * @return なし
 */
void MoveRightCommand::Execute(const int& objectID)
{
	//メッセンジャー
	Messenger* messenger = Messenger::GetInstance();
	//移動キーが押されたら移動状態へ遷移
	messenger->Notify(objectID, Message::MOVING);
	//右方向
	messenger->Notify(objectID, Message::MOVE_RIGHT);
}



