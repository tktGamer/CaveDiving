/**
 * @file   GameObject.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameObject.h"


// オブジェクト番号
int GameObject::s_objectNumber = -1;

// オブジェクトをカウントアップする
int GameObject::CountUpNumber() { return s_objectNumber++; }

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]  objectType オブジェクトの種類
 * @param[in]  modelParams モデルパラメータ
 * 
 */
GameObject::GameObject(ObjectType objectType, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: m_objectType{ objectType }
	, m_graphics{ Graphics::GetInstance() }
	, m_texture{}
	, m_model{ nullptr }
	, m_pCurrentState{ nullptr }
	, m_currentMessage{}
	, m_position{initialPosition} // 初期位置を設定
	, m_quaternion{ DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, initialAngle) } // 初期クォータニオンを設定
	, m_scale{ 1.0f, 1.0f, 1.0f } // 初期拡大率を設定
	, m_parent{ parent }
	, m_currentPosition{}
	, m_currentAngle{}
{
}

/**
 * @brief デストラクタ
 */
GameObject::~GameObject()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject::Initialize()
{

}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject::Finalize()
{

}



/**
 * @brief テクスチャを設定する
 *
 * @param[in] tex テクスチャ
 *
 * @return なし
 */
void GameObject::SetTexture(ID3D11ShaderResourceView** tex)
{
	m_texture = tex;
}

/**
 * @brief テクスチャを取得する
 *
 * @param[in] なし
 *
 * @return テクスチャ
 */
ID3D11ShaderResourceView** GameObject::GetTexture()
{
	return m_texture;
}


/**
 * @brief オブジェクトの種類を取得する
 *
 * @param[in] なし
 *
 * @return オブジェクトの種類
 */
GameObject::ObjectType GameObject::GetObjectType() const
{
	return m_objectType;
}

/**
 * @brief グラフィックスクラスのポインタを取得する
 *
 * @param[in] なし
 *
 * @return グラフィックスクラスのポインタ
 */
Graphics* GameObject::GetGraphics() const
{
	return m_graphics;
}
