/**
 * @file   PartObject.cpp
 *
 * @brief  オブジェクトを構成する体の一部に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2025/12/02
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PartObject.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] root 所持するキャラクタークラス
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
PartObject::PartObject(Character* root,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:GameObject{ Tag::ObjectPart,parent,initialPosition,initialAngle }
	, m_parentCharacter{ root }
{
}



/**
 * @brief デストラクタ
 */
PartObject::~PartObject()
{

}


/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void PartObject::OnMessegeAccepted(Message::MessageID messageID)
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
Character* PartObject::GetRootCharacter()
{
	return m_parentCharacter;
}
