/**
 * @file   CollisionManager.h
 *
 * @brief  当たり判定管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付  2026/01/17
 */

 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Graphics.h"
#include "Game/Object/GameObject3D.h"
#include "../Collision/Sphere.h"
#include "../Collision/Box.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 当たり判定管理
  */
class CollisionManager
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:

// デストラクタ
	~CollisionManager();

// 操作
	// CollisionManagerクラスのインスタンスを取得する
	static CollisionManager* const GetInstance();
	//オブジェクトの登録
	void Register(GameObject3D* obj);
	//オブジェクトの解除
	void UnRegister(GameObject3D* obj);
	//オブジェクトの削除
	void AllRelease();
	//衝突総判定
	void CollisionCheck();
	//終了処理
	void Finalize();
	//押し出し処理
	DirectX::SimpleMath::Vector3 PushOut(Shape* shape1, Shape* shape2);
	//球・球
	DirectX::SimpleMath::Vector3 SphereToSpherePushOut(Sphere* sphereA, Sphere* sphereB);
	//AABB・球
	DirectX::SimpleMath::Vector3 BoxToSpherePushOut(Box* box, Sphere* sphere);
	//AABB・AABB
	DirectX::SimpleMath::Vector3 BoxToBoxPushOut(Box* box, Box* box2);
	//球内への押し戻し
	DirectX::SimpleMath::Vector3 PushBack(Sphere* sphereA, Sphere* sphereB);
	//接触点を調べる
	DirectX::SimpleMath::Vector3 CheckContactPoint(Shape* shapeA, Shape* shapeB);

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
private:
	// コンストラクタ
	CollisionManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const CollisionManager&) = delete;
	// インスタンスをムーブすることを禁止する
	CollisionManager& operator= (CollisionManager&&) = delete;
	// コピーコンストラクタは禁止する
	CollisionManager(const CollisionManager&) = delete;
	// ムーブコンストラクタは禁止する
	CollisionManager(CollisionManager&&) = delete;
//　内部操作
private:
	//接触点
	DirectX::SimpleMath::Vector3 ContactPointSphereToSphere(Sphere* shapeA, Sphere* shapeB);
	DirectX::SimpleMath::Vector3 ContactPointSphereToBox(Sphere* shapeA, Box* shapeB);

// データメンバの宣言 -----------------------------------------------
private:
	// CollisionManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<CollisionManager> s_collisionManager;
	//当たり判定するオブジェクトのリスト
	std::list<GameObject3D*> m_objects;
};