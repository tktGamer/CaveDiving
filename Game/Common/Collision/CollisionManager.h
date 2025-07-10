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
#include"Game/Common/Graphics.h"
#include"Game/Common/Collision/Box.h"
#include"Game/Common/Collision/Sphere.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief CollisionManager
  */
class CollisionManager
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	Graphics* m_graphics;	// グラフィックスクラスのポインタ
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	CollisionManager();

	// デストラクタ
	~CollisionManager();


// 操作
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();
	//押し出し処理
	DirectX::SimpleMath::Vector3 PushOut(Box* shape1, Sphere* shape2);
//　取得・設定
public:

//　内部操作
private:

};

