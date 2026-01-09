/**
 * @file   Hand.h
 *
 * @brief  プレイヤーの手に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/08
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/PartObject.h"
#include"Game/Object/Weapon.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief プレイヤーの手
  */
class Hand : public PartObject
{
// クラス定数の宣言 -------------------------------------------------
private:	
	//プレイヤーの手のアウトラインの太さ
	static constexpr  float PLAYER_HAND_OUTLINE_THICKNESS = 0.04f;
public:


// データメンバの宣言 -----------------------------------------------
private:


	//持っている武器
	std::unique_ptr<Weapon> m_weapon;

	DirectX::SimpleMath::Quaternion m_motionAngle;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Hand(Character* root,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~Hand();


// 操作
public:
	//初期化
	void Initialize() override;
	//更新
	void Update(const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;

	//描画
	void Draw() override;
	//終了
	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);

	//衝突応答分岐
	void CollisionResponce(GameObject* other) override;
	
	//武器を持たせる
	bool HaveWeapon(std::unique_ptr<Weapon> weapon);
//　取得・設定
public:

	DirectX::SimpleMath::Quaternion GetMotionAngle() const;
	void SetMotionAngle(DirectX::SimpleMath::Quaternion angle);
//　内部操作
private:

};

