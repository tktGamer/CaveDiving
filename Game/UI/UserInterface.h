/**
 * @file   UserInterface.h
 *
 * @brief  ユーザーインターフェイスに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/01
 */
 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Interface/IUI.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ユーザーインターフェイス
  */
class UserInterface : public IUI
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
	void SetWindowSize(const int& width, const int& height);
	//拡大率の設定
	void SetScale(const DirectX::SimpleMath::Vector2& scale);
	//拡大率の取得
	const DirectX::SimpleMath::Vector2& GetScale() const { return m_scale; }
	//ベースの拡大率の取得
	const DirectX::SimpleMath::Vector2& GetBaseScale() const { return m_baseScale; }
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
	//テクスチャの設定
	void SetTexture(const wchar_t* path);
	void SetTexture(ID3D11ShaderResourceView** texture);
	//テクスチャの取得
	ID3D11ShaderResourceView* const* GetTexture() { return m_texture; };
	//テクスチャサイズ取得
	const DirectX::SimpleMath::Vector2& GetTextureSize() const { return { static_cast<float>(m_textureWidth),static_cast<float>(m_textureHeight)}; };
	//プリミティブバッチの取得
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>& GetBatch() { return *m_batch.get(); };
// コンストラクタ/デストラクタ
	// コンストラクタ
	UserInterface();
	// デストラクタ
	~UserInterface();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();
	//終了
	void Finalize();
	//生成
	void Create( const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const ANCHOR& anchor
		);
//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// テクスチャハンドル
	ID3D11ShaderResourceView** m_texture;
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;

	int m_windowWidth, m_windowHeight;
	int m_textureWidth, m_textureHeight;
	//大きさ
	DirectX::SimpleMath::Vector2 m_scale;
	DirectX::SimpleMath::Vector2 m_baseScale;
	DirectX::SimpleMath::Vector2 m_position;

	ANCHOR m_anchor;

	float m_renderRatio;
	float m_renderRatioOffset;

};