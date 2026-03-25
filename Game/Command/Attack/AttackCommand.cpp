/**
 * @file   AttackCommand.cpp
 *
 * @brief  攻撃コマンドに関するソースファイル
 *
 * @author 制作者名　福地貴翔　
 *
 * @date   日付　2026/03/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "AttackCommand.h"
#include "Game/Message/Messenger.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */

AttackCommand::AttackCommand()
	:
	ICommand{}
{
}

/**
 * @brief デストラクタ
 */
AttackCommand::~AttackCommand()
{
}

/**
 * @brief コマンド実行
 *
 * @param[in] objectID  コマンドを送るオブジェクトの番号
 *
 * @return なし
 */
void AttackCommand::Execute(const int& objectID)
{
	//メッセンジャー
	Messenger* messenger = Messenger::GetInstance();
	//攻撃状態へ遷移
	messenger->Notify(objectID, Message::ATTACK);
}



