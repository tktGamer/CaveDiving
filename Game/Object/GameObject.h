/**
 * @file   GameObject.h
 *
 * @brief  オブジェクトの基底クラスに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/04/08
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Message/Messenger.h"
#include"Game/Interface/IGameObject.h"
#include"Game/Tag.h"
#include"Game/World.h"
#include <wrl/client.h>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief オブジェクトの基底
  */
class GameObject : public IGameObject
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//生きているか
	virtual bool IsAlive() const { return true; };
	//テクスチャの設定
	void SetTexture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex) { m_texture = tex; };
	//テクスチャの取得
	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetTexture() const { return m_texture; };
	// オブジェクトの種類を取得する
	const Tag::ObjectType& GetObjectType() const { return m_objectType; };
	//派生クラスにキャスト
	template<typename T>
	T* Cast();

	//オブジェクト番号をリセットする
	static void ResetObjectNumber();
	// オブジェクトをカウントアップする
	static int CountUpNumber();
	//オブジェクトの番号を取得
	const int& GetObjectNumber() const { return m_objectNumber; };
// コンストラクタ/デストラクタ
	// コンストラクタ
	GameObject(const Tag::ObjectType& objectType);
	// デストラクタ
	virtual ~GameObject();
// 操作
	
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	// オブジェクト番号
	static int s_objectNumber;
	// オブジェクト番号
	int m_objectNumber;
	// オブジェクトの種類
	Tag::ObjectType m_objectType;
	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};

// メンバ関数の定義 ===========================================================
/**
 * @brief 派生クラスにキャスト
 *
 * @tparam T キャスト先の型
 *
 * @return キャスト後のポインタ、失敗した場合はnullptr
 */
template<typename T>
inline T* GameObject::Cast()
{
	if (dynamic_cast<T*>(this))
	{
		return dynamic_cast<T*>(this);
	}
	return nullptr;
}
