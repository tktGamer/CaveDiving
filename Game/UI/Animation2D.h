/**
 * @file   Animation2D.h
 *
 * @brief  2Dのアニメーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/02/01
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/UI/UserInterface.h"
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief アニメーションテクスチャ
  */
class Animation2D :public IUI
{
// クラス定数の宣言 -------------------------------------------------
public:
	//アニメーションテクスチャ情報
	struct AnimationTexture 
	{
		//全フレーム枚数
		int frameCount;
		//横の枚数
		int frameWidth;
		//縦の枚数
		int frameHeight;

	};

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//ウィンドウサイズの設定
	void SetWindowSize(const DirectX::SimpleMath::Vector2& windowSize);
	//アニメーションが終了したか
	bool IsFinish() const;
// コンストラクタ/デストラクタ
	// コンストラクタ
	Animation2D(const wchar_t* texturepath, const AnimationTexture& textureInfo,const float& animationTime, const bool& isLoop,
		const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale = DirectX::SimpleMath::Vector2::One);
	// デストラクタ
	~Animation2D();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Render();
	//終了
	void Finalize();
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//ウィンドウサイズ
	int m_windowWidth, m_windowHeight;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	//アニメーションするテクスチャハンドルのポインタ
	ID3D11ShaderResourceView** m_pAnimation2DTexture;
	//テクスチャの情報
	AnimationTexture m_textureInfo;
	//テクスチャの大きさ
	DirectX::SimpleMath::Vector2 m_textureSize;
	DirectX::SimpleMath::Vector2 m_frameSize;
	//大きさ
	DirectX::SimpleMath::Vector2 m_scale;
	//座標
	DirectX::SimpleMath::Vector2 m_position;

	UserInterface::ANCHOR m_anchor;

	float m_renderRatio;
	float m_renderRatioOffset;

	//現在のフレーム
	int m_currentFrame = 0;
	//繰り返すか
	bool m_loop;
	//アニメーション時間
	float m_animationTime;
	//経過時間
	float m_currentTime = 0.0f;
};

