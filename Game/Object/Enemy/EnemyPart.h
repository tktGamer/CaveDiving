/**
 * @file   EnemyPart.h
 *
 * @brief  敵の体の一部に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔　
 *
 * @date   日付　2026/01/18
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "Game/Object/PartObject.h"
#include"../Character.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 敵の体の一部
  */
class EnemyPart : public PartObject
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	EnemyPart(Character* root,
		const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	virtual ~EnemyPart();
// 操作
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:

};