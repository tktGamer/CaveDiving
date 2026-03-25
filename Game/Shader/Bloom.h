/**
 * @file   Bloom.h
 *
 * @brief  DirectXのBloom機能に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"RenderTexture.h"
#include "PostProcess.h"
#include"list"
// クラスの宣言 ===============================================================
class GameObject;
// クラスの定義 ===============================================================
/**
  * @brief DirectXのBloom機能
  */
class Bloom
{
// クラス定数の宣言 -------------------------------------------------
public:
	//非公開定数
private:
	//光らせる閾値（小さいほど多くの部分が光る）
	static constexpr float BLOOM_EXTRACT_THRESHOLD = 0.25f;
	//ブラーの広がり量
	static constexpr float BLOOM_BLUR_AMOUNT = 5.0f;
	//ブラーの明るさ
	static constexpr float BLOOM_INTENSITY = 1.0f;
	//解像度低下度
	static constexpr float BLOOM_DOWNSAMPLE = 2.0f;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	Bloom();
	// デストラクタ
	~Bloom();
// 操作
	//初期化
	void Initialize();
	//描画
	void ExecuteBloom(std::list<GameObject*> objects,std::unique_ptr<DX::RenderTexture>& bloomRT);
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_bloomRT;

	//レンダーテクスチャ（ブラー）
	std::unique_ptr<DX::RenderTexture> m_blur1RT;
	std::unique_ptr<DX::RenderTexture> m_blur2RT;

	//ポストプロセス
	std::unique_ptr<DirectX::BasicPostProcess> m_basicPostProcess;
	//デュアルポストプロセス
	std::unique_ptr<DirectX::DualPostProcess> m_dualPostProcess;
};

