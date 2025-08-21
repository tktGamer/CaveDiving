/**
 * @file   Wing.h
 *
 * @brief  羽に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Object/GameObject.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Wing
  */
class Wing : public GameObject
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ
	// オブジェクト番号
	int m_objectNumber;

	DirectX::SimpleMath::Matrix m_world;


	DirectX::SimpleMath::Quaternion m_motionAngle;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Wing(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// デストラクタ
	~Wing();


// 操作
public:
	void Initialize() override;

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID);
	//　取得・設定
public:
	int GetObjectNumber() override;

	DirectX::SimpleMath::Quaternion GetMotionAngle();
	void SetMotionAngle(DirectX::SimpleMath::Quaternion angle);
//　内部操作
private:

};

