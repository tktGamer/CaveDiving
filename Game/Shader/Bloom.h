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

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief DirectXのBloom機能
  */
class Bloom
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:
	//レンダーテクスチャ （シーン全体）
	std::unique_ptr<DX::RenderTexture> m_offScreenRT;

	//レンダーテクスチャ（ブラー）
	std::unique_ptr<DX::RenderTexture> m_blur1RT;
	std::unique_ptr<DX::RenderTexture> m_blur2RT;

	//ポストプロセス
	std::unique_ptr<DirectX::BasicPostProcess> m_basicPostProcess;
	//デュアルポストプロセス
	std::unique_ptr<DirectX::DualPostProcess> m_dualPostProcess;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Bloom();

	// デストラクタ
	~Bloom();


// 操作
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();
//　取得・設定
public:

//　内部操作
private:

};

