/**
 * @file   GameObjectCasting.h
 *
 * @brief  GameObjectから派生クラスへキャストに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付 2025/09/02
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Graphics.h"
#include "Game/Object/GameObject.h"
#include"Game/Object/Character.h"
#include"Game/Object/Weapon.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 当たり判定管理
  */
class CastingToGameObject
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:

	template<typename T>
	T* Cast(GameObject* obj);
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	CastingToGameObject();
	// インスタンスをコピーすることを禁止する
	void operator=(const CastingToGameObject&) = delete;
	// インスタンスをムーブすることを禁止する
	CastingToGameObject& operator= (CastingToGameObject&&) = delete;
	// コピーコンストラクタは禁止する
	CastingToGameObject(const CastingToGameObject&) = delete;
	// ムーブコンストラクタは禁止する
	CastingToGameObject(CastingToGameObject&&) = delete;

	// デストラクタ
	~CastingToGameObject();


// 操作
public:
	// CastingToGameObjectクラスのインスタンスを取得する
	static CastingToGameObject* const GetInstance();

//　取得・設定
public:

//　内部操作
private:

};



CastingToGameObject::CastingToGameObject() 
{

}
CastingToGameObject::~CastingToGameObject() 
{

}

template<typename T>
inline T* CastingToGameObject::Cast(GameObject* obj)
{
	if (dynamic_cast<T*>(obj)) 
	{
		return dynamic_cast<T*>(obj);
	}
	return nullptr;
}
