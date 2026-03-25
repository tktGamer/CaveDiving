/**
 * @file   RenderPipeLine.h
 *
 * @brief  描画に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/22
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "Game/Object/GameObject.h"
#include"Game/Shader/Bloom.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 描画
  */
class RenderPipeLine
{
// クラス定数の宣言 -------------------------------------------------
public:
	//描画レイヤー
	enum class RenderLayer
	{
		Background,
		Stage,
		Character,
		Item,
		Particle,
		UI
	};
//非公開定数
private:
	//解像度低下度
	static constexpr float DOWNSAMPLE = 2.0f;
	//深度クリア値
	static constexpr float CLEAR_DEPTH = 1.0f;
	// Bloom合成パラメータ
	static constexpr float BLOOM_COMBINE_INTENSITY = 1.25f; // 発光強度
	static constexpr float BLOOM_BASE_INTENSITY = 1.0f;  // 元画像の明るさ
	static constexpr float BLOOM_SATURATION = 0.0f;  // 彩度（0でデフォルト）
	static constexpr float BLOOM_BASE_SATURATION = 1.0f;  // 元画像の彩度
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:

// コンストラクタ/デストラクタ
	// コンストラクタ
	RenderPipeLine();
	// デストラクタ
	~RenderPipeLine();
// 操作
	//オブジェクト登録
	void Register(const RenderLayer& layer, GameObject* object);
	//オブジェクト登録解除
	void UnRegister(GameObject* object);
	//描画
	void Render();
	//画面サイズ変更時の処理
	void ReSize();
//　内部操作
private:
	//通常描画
	void NormalPass();
	//ブルーム描画
	void BloomPass();
	//合成描画
	void BlendPass();
// データメンバの宣言 -----------------------------------------------
private:
	//レイヤーとオブジェクトを管理するマップ
	std::unordered_map<RenderLayer, std::vector<GameObject*>> m_renderObjects;
	
	//レンダーテクスチャ （シーン全体）
	std::unique_ptr<DX::RenderTexture> m_offScreenRT;
	//レンダーテクスチャ（ブルーム抽出）
	std::unique_ptr<DX::RenderTexture> m_bloomRT;
	//デュアルポストプロセス
	std::unique_ptr<DirectX::DualPostProcess> m_dualPostProcess;
	//ブルームクラス
	std::unique_ptr<Bloom> m_bloom;
};