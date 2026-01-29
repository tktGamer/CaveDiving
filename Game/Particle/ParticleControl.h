/**
 * @file   ParticleControl.h
 *
 * @brief  パーティクルコントロールの基底に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/28
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include <list>
#include <string>
#include <SimpleMath.h>
#include"../Particle/Particle.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクルコントロールの基底
  */
class ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:
	//カメラの情報
	struct CameraBuffer
	{
		DirectX::SimpleMath::Vector3 cameraPos; // カメラの右方向ベクトル
		float dummy1 = 0;
		DirectX::SimpleMath::Vector3 cameraUp; // カメラの上方向ベクトル
		float dummy2 = 0;
	};

	//時間と座標
	struct TimerAndPos
	{
		//経過時間
		float timer = 0.0f;
		//パーティクルの発生位置
		DirectX::SimpleMath::Vector3 pos = { 0,0,0 };
	};


// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//頂点があるか
	bool HasVertex() const;
	//テクスチャの取得
	ID3D11ShaderResourceView** GetTexture() const;
// コンストラクタ/デストラクタ
public:
	//コンストラクタ
	ParticleControl(const wchar_t* texturePath);
	//デストラクタ
	virtual ~ParticleControl();
// 操作
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp) = 0;
	//リセット
	virtual void Reset() = 0;

	//パーティクルの更新
	void UpdateParticles();
	//パーティクル作成
	void AddParticle(std::unique_ptr<Particle> pParticle);
	//パーティクルリスト取得
	std::list<std::unique_ptr<Particle>>& GetParticleList();
	//パーティクルの消去
	void ClearParticles();
	//頂点生成
	void CreateVertex(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const std::function<void()>& customCreate = nullptr);
	//頂点追加
	void AddVertex(const DirectX::VertexPositionColorTexture& vPCT);
	//頂点消去
	void ClearVertex();
	//発生位置・タイマー追加
	void AddTimerAndPos(const TimerAndPos& timerAnPos);
	//発生位置・タイマーの取得
	std::vector<TimerAndPos>& GetTimerAndPos();
	//発生位置・タイマーの消去
	void ClearTimerAndPos();
	//カメラの情報をバッファに渡す
	void SetCameraBuffer(const CameraBuffer& cameraCB, const UINT& startSlot = 1, const UINT& numBuffer = 1);
	//シェーダー関連の設定
	void SetShaderState() const;
	//描画バッチ処理
	void DrawBatch(const std::function<void()>& customDraw = nullptr);
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
	//カメラのコンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cameraCBuffer;
	//	パーティクルの発生位置とタイマー
	std::vector<TimerAndPos> m_timerAndPos;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	頂点情報のリスト
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	// テクスチャハンドル
	ID3D11ShaderResourceView** m_texture;
	//パーティクルのリスト
	std::list<std::unique_ptr<Particle>> m_particles;
};