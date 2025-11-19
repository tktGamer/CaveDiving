/**
 * @file   ParticleDamageNumber.h
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
#include"../Damage/ParticleNumber3D.h"



// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleDamageNumber : public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	変数


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

	//	頂点情報のリスト
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;

	//	パーティクルに使う情報を保存するためのクラスオブジェクト用リスト
	std::list<ParticleNumber3D> m_particleNumber;

	
	DirectX::SimpleMath::Vector3 m_basePosition;
	DirectX::SimpleMath::Matrix m_billboard;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleDamageNumber(
		const std::string& texturePsth,
		const DirectX::SimpleMath::Vector3& pos,
		const int& number);
	//	デストラクタ
	~ParticleDamageNumber();

// 操作
public:
	//	更新
	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);

	void Reset();

public:
	bool IsDelete();
private:
	int CheckDigit(const int& num);

	void CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up);

};

