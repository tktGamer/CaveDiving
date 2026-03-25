/**
 * @file   PartObject.h
 *
 * @brief  オブジェクトを構成する体の一部に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/25
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
	//角度制限
	struct RotationLimit
	{
		DirectX::SimpleMath::Vector3 min = DirectX::SimpleMath::Vector3::Zero;
		DirectX::SimpleMath::Vector3 max = DirectX::SimpleMath::Vector3::Zero;
		bool enable = false;

		// staticメンバとしてOFFを定義
		static const RotationLimit OFF;
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//大元のキャラクターを取得
	Character* GetRootCharacter();
	//角度制限を考慮して角度を設定
	void SetLocalRotationEuler(const DirectX::SimpleMath::Vector3& eulerAngle);
	//ローカル角度を取得
	const DirectX::SimpleMath::Vector3& GetLocalEuler();
	//角度制限設定
	void SetRotationLimit(const RotationLimit& rotationLimit);
	//生きているか
	bool IsAlive() const override;

// コンストラクタ/デストラクタ
	// コンストラクタ
	PartObject(Character* root,
		const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	virtual ~PartObject();
// 操作
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//角度制限をオフ
	void RotationLimitOFF();
	//角度制限をオフ
	void RotationLimitON();
//　内部操作
private:
// データメンバの宣言 -----------------------------------------------
private:
	//所有者のキャラクター
	Character* m_parentCharacter;

	// 現在のローカル角度
	DirectX::SimpleMath::Vector3 m_localEuler; 
	//角度制限
	RotationLimit m_rotationLimit;
};
