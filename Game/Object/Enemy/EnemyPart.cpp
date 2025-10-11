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
	:GameObject{Tag::EnemyPart,parent,initialPosition,initialAngle}
	,m_parentCharacter{root}
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

/**
 * @brief 部品をもつキャラクターの取得
 *
 * @param[in] なし
 *
 * @return 部品をもつキャラクター
 */
Character* EnemyPart::GetRootCharacter()
{
	return m_parentCharacter;
}
