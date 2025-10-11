/**
 * @file   ParticleControl.h
 *
 * @brief  パーティクルコントロールの基底関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include <list>



// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクルコントロールの基底
  */
class ParticleControl
{
	// クラス定数の宣言 -------------------------------------------------
private:

	struct TimerAndPos
	{
		//経過時間
		float timer = 0.0f;
		//パーティクルの発生位置
		DirectX::SimpleMath::Vector3 pos = { 0,0,0 };
	};
	// データメンバの宣言 -----------------------------------------------
private:
	//	パーティクルの発生位置とタイマー
	std::vector<TimerAndPos> m_timerAndPos;

	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;


	//	頂点情報のリスト
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;


	// テクスチャハンドル
	ID3D11ShaderResourceView** m_texture;
	//	カメラに関する情報
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	DirectX::SimpleMath::Vector3 m_cameraTarget;



	DirectX::SimpleMath::Matrix m_billboard;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	ParticleControl(const std::string& texturePath);
	~ParticleControl();
	// 操作
public:


	virtual void Update() = 0;

	virtual void Render() = 0;

	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up);

	void Reset();
//　取得・設定
public:
	const DirectX::SimpleMath::Vector3& GetCameraPosition() const;
	const DirectX::SimpleMath::Vector3& GetCameraTarget() const;

	const DirectX::SimpleMath::Matrix& GetBillBoard() const;

	//テクスチャの取得
	ID3D11ShaderResourceView** GetTexture() const;

private:

};
