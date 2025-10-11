/**
 * @file   GolemHand.h
 *
 * @brief  ゴーレムの手に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
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
public:


// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ

	//球状当たり判定
	Sphere m_sphere;

	Ito::DisplayCollision m_display;

	//持っている武器
	std::unique_ptr<Weapon> m_weapon;

	DirectX::SimpleMath::Quaternion m_motionAngle;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	GolemHand(Character* root, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);

	// デストラクタ
	~GolemHand();


// 操作
public:
	void Initialize() override;

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

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

