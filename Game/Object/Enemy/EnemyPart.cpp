/**
 * @file   EnemyPart.cpp
 *
 * @brief  敵の体の一部に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyPart.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] root  所有されているクラス
 * @param[in] parent　親クラスのポインタ
 * @param[in] transform  
 */
EnemyPart::EnemyPart(Character* root, const GameObject3D* parent, const Transform& transform)
	:
	PartObject{root,parent,transform}
{
}

/**
 * @brief デストラクタ
 */
EnemyPart::~EnemyPart()
{
}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void EnemyPart::OnMessegeAccepted(Message::MessageID messageID)
{
	messageID;
}