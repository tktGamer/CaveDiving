/**
 * @file   PartObject.h
 *
 * @brief  オブジェクトを構成する体の一部に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/10/21
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Object/GameObject.h"
#include"../Object/Character.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief オブジェクトを構成する体の一部
  */
class PartObject : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:

	//所有者のキャラクター
	Character* m_parentCharacter;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	PartObject(Character* root,
		 GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	virtual ~PartObject();


// 操作
public:
	//
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

//　取得・設定
public:

	//大元のキャラクターを取得
	Character* GetRootCharacter();
//　内部操作
private:

};

