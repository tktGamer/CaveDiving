/**
 * @file   EnemyPart.cpp
 *
 * @brief  敵の体の一部に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyPart.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] 
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
EnemyPart::EnemyPart(Character* root, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:PartObject{root,parent,initialPosition,initialAngle}
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
	switch (messageID) 
	{

	}
}

