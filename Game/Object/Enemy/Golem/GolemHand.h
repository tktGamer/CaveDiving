/**
 * @file   GolemHand.h
 *
 * @brief  ゴーレムの手に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/19
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../EnemyPart.h"
#include"Game/Common/Collision/Sphere.h"
// クラスの宣言 ===============================================================
class Weapon;
// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの手
  */
class GolemHand : public EnemyPart
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//球の当たり判定サイズ
	static constexpr float GOLEM_HAND_SPHERE_SIZE = 2.5f;
	//ゴーレムのアウトラインの太さ
	static constexpr  float GOLEM_HAND_OUTLINE_THICKNESS = 0.04f;

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:

	DirectX::SimpleMath::Quaternion GetMotionAngle();
	void SetMotionAngle(DirectX::SimpleMath::Quaternion angle);
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemHand(Character* root,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	~GolemHand();
// 操作
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
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//球状当たり判定
	Sphere m_sphere;
	//持っている武器
	std::unique_ptr<Weapon> m_weapon;

	DirectX::SimpleMath::Quaternion m_motionAngle;
};