/**
 * @file   CollisionManager.h
 *
 * @brief  CollisionManagerに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付 2025/08/22
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Graphics.h"
#include "Game/Object/GameObject.h"
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


// データメンバの宣言 -----------------------------------------------
private:
	// CollisionManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<CollisionManager> s_collisionManager;


	//当たり判定するオブジェクトのリスト
	std::list<GameObject*> m_objects;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
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

	// デストラクタ
	~CollisionManager();


// 操作
public:
	// CollisionManagerクラスのインスタンスを取得する
	static CollisionManager* const GetInstance();

	//オブジェクトの登録
	void Register(GameObject* obj);
	//オブジェクトの解除
	void UnRegister(GameObject* obj);
	

	//オブジェクトの削除
	void AllRelease();

	void Update();

	//衝突総判定
	void CollisionCheck();

	void Finalize();
	//押し出し処理
	DirectX::SimpleMath::Vector3 PushOut(Box* box, Sphere* sphere);
	DirectX::SimpleMath::Vector3 PushOut(Box* box, Box* box2);
//　取得・設定
public:

//　内部操作
private:

};

