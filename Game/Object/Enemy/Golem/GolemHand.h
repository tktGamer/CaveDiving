/**
 * @file   GolemHand.h
 *
 * @brief  ゴーレムの手に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/04
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../EnemyPart.h"
#include"Game/Object/Weapon.h"
#include"Game/Common/Collision/Sphere.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief GolemHand
  */
class GolemHand : public EnemyPart
{
// クラス定数の宣言 -------------------------------------------------
private:
	//球の当たり判定サイズ
	static constexpr float GOLEM_HAND_SPHERE_SIZE = 2.5f;
	//ゴーレムのアウトラインの太さ
	static constexpr  float GOLEM_HAND_OUTLINE_THICKNESS = 0.04f;
public:


// データメンバの宣言 -----------------------------------------------
private:

	//球状当たり判定
	Sphere m_sphere;

	//持っている武器
	std::unique_ptr<Weapon> m_weapon;

	DirectX::SimpleMath::Quaternion m_motionAngle;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemHand(Character* root,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~GolemHand();


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

	DirectX::SimpleMath::Quaternion GetMotionAngle();
	void SetMotionAngle(DirectX::SimpleMath::Quaternion angle);
//　内部操作
private:

};

