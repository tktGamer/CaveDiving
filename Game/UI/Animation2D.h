/**
 * @file   Animation2D.h
 *
 * @brief  2Dのアニメーションに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/11
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"Game/UI/UserInterface.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 数字
  */
class Animation2D
{
// クラス定数の宣言 -------------------------------------------------
public:
	struct AnimationTexture 
	{
		//全フレーム枚数
		int frameCount;
		//横の枚数
		int frameWidth;
		//縦の枚数
		int frameHeight;

	};

// データメンバの宣言 -----------------------------------------------
private:
	// グラフィックスクラスのポインタ
	Graphics* m_graphics;	

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	//アニメーションするテクスチャハンドルのポインタ
	ID3D11ShaderResourceView** m_pAnimation2DTexture;
	int m_windowWidth, m_windowHeight;
	DirectX::SimpleMath::Vector2 m_textureSize;
	DirectX::SimpleMath::Vector2 m_frameSize;

	DirectX::SimpleMath::Vector2 m_scale;
	DirectX::SimpleMath::Vector2 m_baseScale;
	DirectX::SimpleMath::Vector2 m_position;

	UserInterface::ANCHOR m_anchor;

	float m_renderRatio;
	float m_renderRatioOffset;

	AnimationTexture m_textureInfo;
	//現在のフレーム
	int m_currentFrame = 0;
	//繰り返すか
	bool m_loop;
	//アニメーション時間
	float m_animationTime;
	//経過時間
	float m_currentTime = 0.0f;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Animation2D(const wchar_t* texturepath, const AnimationTexture& textureInfo,const float& animationTime, const bool& isLoop,
		const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale = DirectX::SimpleMath::Vector2::One);

	// デストラクタ
	~Animation2D();


// 操作
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();
//　取得・設定
public:
	void SetWindowSize(const DirectX::SimpleMath::Vector2& windowSize);
	//アニメーションが終了したか
	bool IsFinish() const;
//　内部操作
private:

};

