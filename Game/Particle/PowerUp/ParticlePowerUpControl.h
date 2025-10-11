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
#include<list>

#include"../PowerUp/ParticlePowerUp.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticlePowerUpControl
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

	struct TimerAndPos
	{
		//経過時間
		float timer = 0.0f;
		//パーティクルの発生位置
		DirectX::SimpleMath::Vector3 pos = { 0,0,0 };
	};
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};
	// データメンバの宣言 -----------------------------------------------
private:

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
	//	カメラに関する情報
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	DirectX::SimpleMath::Vector3 m_cameraTarget;


	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	DirectX::SimpleMath::Matrix m_billboard;

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
