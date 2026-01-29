/**
 * @file   Pikel.h
 *
 * @brief  つるはし（プレイヤーの武器）に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/20
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Weapon.h"
#include"Game/Common/Collision/DisplayCollision.h"
#include"Game/Common/Collision/Sphere.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief つるはし（プレイヤーの武器）
  */
class Pikel : public Weapon
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	//ピッケルの球状当たり判定サイズ
	static constexpr float PIKEL_SPHERE_SIZE = 1.3f;
	//ピッケルの当たり判定位置調整
	static constexpr DirectX::SimpleMath::Vector3 PIKEL_COLLSION_POS_OFFSET = {0.0f,1.0f,0.0f};


// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	Pikel(Character* owner,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	~Pikel();
// 操
	//初期化
	void Initialize();
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
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:

	// メッセージID
	Message::MessageID m_messageID;

	Ito::DisplayCollision m_display;
	//当たり判定
	Sphere m_sphere;
};