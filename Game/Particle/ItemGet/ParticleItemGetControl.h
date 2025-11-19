/**
 * @file   ParticleItemGetControl.h
 *
 * @brief  パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付 2025/11/19
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include <list>


#include"../ItemGet/ParticleItemGet.h"
#include"../ParticleControl.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleItemGetControl :public ParticleControl
{
	// クラス定数の宣言 -------------------------------------------------
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



	std::list<ParticleItemGet> m_particleItemGet;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticleItemGetControl(const std::string& texturePath);
	~ParticleItemGetControl();
	// 操作
public:


	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);


	void RequestItemGetParticle(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		const DirectX::SimpleMath::Vector3& targetPos,//向かっていくオブジェクトの位置
		const DirectX::SimpleMath::Color& color
		);
	
	void Reset();
//　取得・設定
public:

private:

};
