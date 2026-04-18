/**
 * @file   GolemArm.h
 *
 * @brief  ゴーレムの腕に関するヘッダファイル
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
class GolemHand;
// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの腕
  */
class GolemArm : public EnemyPart
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//球の当たり判定サイズ
	static constexpr float GOLEM_ARM_SPHERE_SIZE = 1.0f;
	//ゴーレムのアウトラインの太さ
	static constexpr  float GOLEM_ARM_OUTLINE_THICKNESS = 0.04f;
	//手の初期位置	
	static constexpr DirectX::SimpleMath::Vector3 HAND_INIT_POS = { 0.0f, -4.0f,0.0f };
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:

	const DirectX::SimpleMath::Quaternion& GetMotionAngle();
	void SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle);
// コンストラクタ/デストラクタ
	// コンストラクタ
	GolemArm(Character* root,const GameObject3D* parent, const Transform& transform);
	// デストラクタ
	~GolemArm();
// 操作
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//終了
	void Finalize();
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//衝突応答分岐
	void CollisionResponce(GameObject3D* other) override;
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//球状当たり判定
	Sphere m_sphere;

	DirectX::SimpleMath::Quaternion m_motionAngle;

	//子オブジェクト
	std::unique_ptr<PartObject> m_hand;
};