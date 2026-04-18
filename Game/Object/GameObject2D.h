/**
 * @file   GameObject2D.h
 *
 * @brief  2Dのオブジェクトの基底クラスに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/25
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
#include"Game/Object/GameObject.h"
#include"Game/Common/Collision/Shape.h"
#include"Game/Tag.h"
#include"Game/World.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief オブジェクトの基底
  */
class GameObject2D : public GameObject
{
	// クラス定数の宣言 -------------------------------------------------
public:
	//UIのアンカーポイント
	enum ANCHOR
	{
		TOP_LEFT = 0,
		TOP_CENTER,
		TOP_RIGHT,

		MIDDLE_LEFT,
		MIDDLE_CENTER,
		MIDDLE_RIGHT,

		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//ウィンドウサイズの設定
	void SetBaseWindowSize(const int& width, const int& height) { m_windowWidth = width; m_windowHeight = height; };
	//ウィンドウサイズの設定
	const DirectX::SimpleMath::Vector2& GetBaseWindowSize() { return { static_cast<float>(m_windowWidth),static_cast<float>(m_windowHeight) }; };
	//拡大率の設定
	void SetScale(const DirectX::SimpleMath::Vector2& scale);
	//拡大率の取得
	const DirectX::SimpleMath::Vector2& GetScale() const { return m_scale; }
	//描画座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector2& position);
	//描画座標の取得
	const DirectX::SimpleMath::Vector2& GetPosition() const { return m_position; }
	//アンカー位置の設定
	void SetAnchor(const ANCHOR& anchor);
	//アンカー位置の取得
	const ANCHOR& GetAnchor() const { return m_anchor; }
	//描画比率の設定
	void SetRenderRatio(const float& ratio);
	//描画比率の取得
	const float& GetRenderRatio() const { return m_renderRatio; }
	//レンダリングオフセットの設定
	void SetRenderRatioOffset(const float& offset);
	//レンダリングオフセットの取得
	const float& GetRenderRatioOffset() const { return m_renderRatioOffset; }
	//テクスチャサイズ取得
	const DirectX::SimpleMath::Vector2& GetTextureSize() const { return { static_cast<float>(m_textureWidth),static_cast<float>(m_textureHeight) }; };
	//プリミティブバッチの取得
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>& GetBatch() { return *m_batch.get(); };
	// コンストラクタ/デストラクタ
	// コンストラクタ
	GameObject2D(const Tag::ObjectType& objectType,const GameObject2D* parent = nullptr,
		const DirectX::SimpleMath::Vector2& initialPosition = DirectX::SimpleMath::Vector2::Zero,
		const DirectX::SimpleMath::Vector2& initialScale = DirectX::SimpleMath::Vector2::Zero);
	// デストラクタ
	virtual ~GameObject2D();
// 操作
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update()=0;
	//描画
	virtual void Draw()=0;
	//終了
	virtual void Finalize() = 0;
	//生成
	void Create(const wchar_t* path,
		const ANCHOR& anchor
	);
	//最終座標取得
	const DirectX::SimpleMath::Vector2 GetWorldPosition() const;
	//最終座標取得
	const DirectX::SimpleMath::Vector2 GetWorldScale() const;

//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;

	int m_windowWidth, m_windowHeight;
	int m_textureWidth, m_textureHeight;
	const GameObject2D* m_parent;
	//位置
	DirectX::SimpleMath::Vector2 m_position;
	//サイズ
	DirectX::SimpleMath::Vector2 m_scale;
	//アンカー
	ANCHOR m_anchor;

	//最終位置
	DirectX::SimpleMath::Vector2 m_currentPosition;
	//最終サイズ
	DirectX::SimpleMath::Vector2 m_currentScale;

	float m_renderRatio;
	float m_renderRatioOffset;

};

