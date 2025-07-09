#ifndef GRAPHICS_DEFINED
#define GRAPHICS_DEFINED
/**
 * @file   Graphics.h
 *
 * @brief  グラフィックに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "DeviceResources.h"
#include"Game/Common/DebugFont.h"
// クラスの定義 ===============================================================
/**
 * @brief グラフィック
 */
class Graphics final
{
// 取得/設定
public:
	// Graphicsクラスのインスタンスを取得する
	static Graphics* const GetInstance();
	// デバイスリソースを取得する
	DX::DeviceResources* GetDeviceResources() { return m_deviceResources.get(); }

	// スクリーンサイズを取得する
	void GetScreenSize(int& width, int& height) const { width = m_screenW; height = m_screenH; }
	// スクリーンサイズを設定する
	void SetScreenSize(const int& width, const int& height) { m_screenW = width; m_screenH = height; }
	// PrimitiveBatchクラスのインスタンスを取得する
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* GetPrimitiveBatch() const { return m_primitiveBatch.get(); }
	// InputLayoutクラスのインスタンスを取得する
	ID3D11InputLayout* GetInputLayout() const { return m_inputLayout.Get(); }
	// BasicEffectクラスのインスタンス取得する
	DirectX::BasicEffect* GetBasicEffect() { return m_basicEffect.get(); }
	// CommonStatesクラスのインスタンスを取得する
	DirectX::CommonStates* GetCommonStates() const { return m_commonStates.get(); }
	// SpriteBatchクラスのインスタンスを取得する
	DirectX::SpriteBatch* GetSpriteBatch() { return m_spriteBatch.get(); }
	// SpriteFontクラスのインスタンスを取得する
	DirectX::SpriteFont* GetFont() { return m_spriteFont.get(); }
	// EffectFactoryクラスのインスタンスを取得する
	DirectX::EffectFactory* GetFX() const { return m_effectFactory.get(); }
	// ビュー行列を設定する
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// ビュー行列を取得する
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; };
	// 射影行列を設定する
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection) { m_projection = projection; }
	// 射影行列を取得する
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; };
	//キーボードトラッカーを取得する
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardTracker() { return m_traker.get(); }
	//キーボードトラッカーを更新する
	void UpdateKeyboardTracker(DirectX::Keyboard::State key) { m_traker->Update(key); }

	// デバッグフォントを設定する関数
	void SetDebugFont(Ito::DebugFont* debugFont) { m_debugFont = debugFont; }

	// デバッグフォントを取得する関数
	Ito::DebugFont* GetDebugFont() { return m_debugFont; }

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
private:
	// コンストラクタ
	Graphics();
	// インスタンスをコピーすることを禁止する
	void operator=(const Graphics&) = delete;
	// インスタンスをムーブすることを禁止する
	Graphics& operator= (Graphics&&) = delete;
	// コピーコンストラクタは禁止する
	Graphics(const Graphics&) = delete;
	// ムーブコンストラクタは禁止する
	Graphics(Graphics&&) = delete;

// 操作
public:
	// 初期化する
	void Initialize();
	// デストラクタ
	~Graphics() = default;

	// プリミティブ描画を開始する
	void DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// プリミティブ描画を終了する
	void DrawPrimitiveEnd();

// データメンバの宣言 -----------------------------------------------
private:
	// Graphicsクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<Graphics> s_graphics;
	// デバイスリソース
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;
	// ラスタライザーステート
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterrizerState;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//キーボードトラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_traker;
	Ito::DebugFont* m_debugFont;
	// スクリーンサイズ
	int m_screenW, m_screenH;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	// デバイス
	ID3D11Device* m_device;
	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
};
#endif		// GRAPHICS_DEFINED
