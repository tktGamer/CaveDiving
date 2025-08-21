/**
 * @file   CollisionManager.h
 *
 * @brief  CollisionManagerに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Graphics.h"
#include "Game/Common/Collision/Box.h"
#include "Game/Common/Collision/Sphere.h"
#include "Game/Object/GameObject.h"
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
	// ResourceManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<CollisionManager> s_collisionManager;

	Graphics* m_graphics;	// グラフィックスクラスのポインタ

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
	//オブジェクトの削除
	void AllRelease();
	void Update();

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

