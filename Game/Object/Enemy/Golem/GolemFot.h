/**
 * @file   GolemFot.h
 *
 * @brief  ゴーレムの足に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/03/02
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../EnemyPart.h"
#include"Game/Common/Collision/Box.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ゴーレムの手
  */
class GolemFot : public EnemyPart
{
	// クラス定数の宣言 -------------------------------------------------
public:
	//非公開定数
private:
	//非公開定数
private:
	//当たり判定サイズ
	static constexpr DirectX::SimpleMath::Vector3 GOLEM_FOT_COLLISION_SIZE = { 1.5f,1.0f,1.5f };
	//ゴーレムのアウトラインの太さ
	static constexpr  float GOLEM_FOT_OUTLINE_THICKNESS = 0.04f;

	// メンバ関数の宣言 -------------------------------------------------
	//　取得・設定
public:

	const DirectX::SimpleMath::Quaternion& GetMotionAngle() const;
	void SetMotionAngle(const DirectX::SimpleMath::Quaternion& angle);
	// コンストラクタ/デストラクタ
		// コンストラクタ
	GolemFot(Character* root, const GameObject3D* parent, const Transform& transform);
	// デストラクタ
	~GolemFot();
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
	//当たり判定
	Box m_box;
	Ito::DisplayCollision m_display;

	DirectX::SimpleMath::Quaternion m_motionAngle;
};