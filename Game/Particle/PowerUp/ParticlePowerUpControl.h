/**
 * @file   ParticlePowerUpControl.h
 *
 * @brief  パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

#include"../ParticleControl.h"
#include"../PowerUp/ParticlePowerUp.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticlePowerUpControl : public ParticleControl
{
	// クラス定数の宣言 -------------------------------------------------
private:
	static constexpr int VANISH_PARTICLE_NUM = 14; // 消滅パーティクルの数
	static constexpr DirectX::SimpleMath::Vector3 VANISH_PARTICLE_DIRECTION[VANISH_PARTICLE_NUM] =
	{
		{ 0.0f, 1.0f, 0.0f }, // 上
		{ 0.0f, -1.0f, 0.0f }, // 下
		{ 1.0f, 0.0f, 0.0f }, // 右
		{ 0.0f, 0.0f, 1.0f }, // 前
		{ -1.0f, 0.0f, 0.0f }, // 左
		{ 0.0f, 0.0f, -1.0f }, // 後ろ
		{ -1.0f, -1.0f, -1.0f }, // 左下後ろ
		{ -1.0f, -1.0f, 1.0f }, // 左下前
		{ -1.0f, 1.0f, -1.0f }, // 左上後ろ
		{ -1.0f, 1.0f, 1.0f }, // 左上前
		{ 1.0f, -1.0f, -1.0f }, // 右下後ろ
		{ 1.0f, -1.0f, 1.0f }, // 右下前
		{ 1.0f, 1.0f, -1.0f }, // 右上後ろ
		{ 1.0f, 1.0f, 1.0f }  // 右上前
	};

public:

// データメンバの宣言 -----------------------------------------------
private:

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;


	std::vector<TimerAndPos> m_timerAndPos; //	パーティクルの発生位置とタイマー


	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// テクスチャハンドル
	ID3D11ShaderResourceView** m_texture;
	//	！New！
	//	頂点情報のリスト
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;

	//	パーティクルに使う情報を保存するためのクラスオブジェクト用リスト
	std::list<ParticlePowerUp> m_particlePowerUp;

	const DirectX::SimpleMath::Vector3* m_centerPos;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticlePowerUpControl(const std::string& texturePath);
	~ParticlePowerUpControl();
	// 操作
public:


	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);

	void RequestParticlePowerUp(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		DirectX::SimpleMath::Color color//パーティクルの発生位置
		);
	
	void Reset();
//　取得・設定
public:

private:

};
