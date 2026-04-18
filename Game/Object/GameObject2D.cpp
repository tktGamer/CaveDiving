/**
 * @file   GameObject2D.cpp
 *
 * @brief  ゲーム内のオブジェクトの基底クラスに関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/04/09
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GameObject2D.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in]  objectType オブジェクトの種類
 * @param[in]  parent     親オブジェクト
 * @param[in]  initialPosition 初期座標
 * @param[in]  initialAngle 　初期角度
 * 
 */
GameObject2D::GameObject2D(const Tag::ObjectType& objectType, const GameObject2D* parent,
	const DirectX::SimpleMath::Vector2& initialPosition, const DirectX::SimpleMath::Vector2& initialScale)
	: 
	GameObject{ objectType },
	m_parent{ parent },
	m_position{ initialPosition },
	m_scale{ initialScale },
    m_anchor{GameObject2D::ANCHOR::MIDDLE_CENTER},
    m_textureHeight{},
	m_textureWidth{},
	m_windowHeight{},
	m_windowWidth{},
	m_renderRatio{ 1.0f },
	m_renderRatioOffset{ 0.0f }
{
    //	プリミティブバッチの作成
    m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>
        (Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
}

/**
 * @brief デストラクタ
 */
GameObject2D::~GameObject2D()
{
}

/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject2D::Initialize()
{
}

/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GameObject2D::Finalize()
{
}

/**
 * @brief 生成処理
 *
 * @param[in] path　　  ファイルパス
 * @param[in] position　座標
 * @param[in] scale　　 拡大率
 * @param[in] anchor    アンカー位置
 *
 * @return なし
 */
void GameObject2D::Create(const wchar_t* path, const ANCHOR& anchor)
{
    //アンカー設定
	m_anchor = anchor;
	//画像の設定
	SetTexture(ResourceManager::GetInstance()->RequestTexture(path));
	//テクスチャサイズを取得
	ResourceManager::GetInstance()->GetTextureSize(path, m_textureWidth, m_textureHeight);
}

/**
 * @brief 最終座標取得
 *
 * @param[in] なし
 *
 * @return なし
 */
const DirectX::SimpleMath::Vector2 GameObject2D::GetWorldPosition() const
{
    DirectX::SimpleMath::Vector2 parentScale = DirectX::SimpleMath::Vector2::One;
    DirectX::SimpleMath::Vector2 parentPos = DirectX::SimpleMath::Vector2::Zero;

    if (m_parent)
    {
        parentScale = m_parent->GetWorldScale();
        parentPos = m_parent->GetWorldPosition();
    }

    // 親スケールをローカル位置に掛ける
    DirectX::SimpleMath::Vector2 worldPos = parentPos + m_position * parentScale;

    // アンカー補正（親サイズ × 親スケール）
    DirectX::SimpleMath::Vector2 anchorOffset = {
        m_parent ? m_parent->GetTextureSize().x *  (m_anchor % 3u)* parentScale.x : 0,
        m_parent ? m_parent->GetTextureSize().y *  (m_anchor / 3u)* parentScale.y : 0
    };
    worldPos = worldPos + anchorOffset;


    return worldPos;
}

/**
 * @brief 最終サイズ取得
 *
 * @param[in] なし
 *
 * @return なし
 */
const DirectX::SimpleMath::Vector2 GameObject2D::GetWorldScale() const
{
    DirectX::SimpleMath::Vector2 parentScale = DirectX::SimpleMath::Vector2::One;
    if(m_parent) 
    {
        parentScale = m_parent->GetWorldScale();
    }
    return m_scale * parentScale;
}
