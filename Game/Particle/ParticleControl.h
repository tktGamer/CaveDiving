/**
 * @file   ParticleControl.h
 *
 * @brief  パーティクルコントロールの基底に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2025/10/22
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
protected:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	struct CameraBuffer
	{
		DirectX::SimpleMath::Vector3 cameraPos; // カメラの右方向ベクトル
		float dummy1 = 0;
		DirectX::SimpleMath::Vector3 cameraUp; // カメラの上方向ベクトル
		float dummy2 = 0;
	};


	struct TimerAndPos
	{
		//経過時間
		float timer = 0.0f;
		//パーティクルの発生位置
		DirectX::SimpleMath::Vector3 pos = { 0,0,0 };
	};
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


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticleControl(const wchar_t* texturePath);

	virtual ~ParticleControl();
// 操作
public:

	//更新
	virtual void Update() = 0;
	//描画
	virtual void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp) = 0;


	virtual void Reset() = 0;
//　取得・設定
public:
	//頂点があるか
	bool HasVertex() const;


	//テクスチャの取得
	ID3D11ShaderResourceView** GetTexture() const;

//内部処理
private:

protected:
	//パーティクルの更新
	void UpdateParticles();

	//パーティクル作成
	void AddParticle(std::unique_ptr<Particle> pParticle);
	//パーティクルリスト取得
	std::list<std::unique_ptr<Particle>>& GetParticleList();
	//パーティクルの消去
	void ClearParticles();
	//描画する頂点作成
	//template <typename T>
	//void CreateVertex(const std::list<T>& particleList,const DirectX::SimpleMath::Vector3& target,const DirectX::SimpleMath::Vector3& cameraPos);

	void CreateVertex(const DirectX::SimpleMath::Vector3& target,const DirectX::SimpleMath::Vector3& cameraPos, const std::function<void()>& customCreate = nullptr);
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
	void SetCameraBuffer(const CameraBuffer& cameraCB , const UINT& startSlot = 1, const UINT& numBuffer = 1);

	//シェーダー関連の設定
	void SetShaderState() const;

	//描画バッチ処理
	void DrawBatch(const std::function<void()>& customDraw = nullptr);
};

// メンバ関数の定義 -------------------------------------------------
/**
 * @brief パーティクル情報から頂点リストを生成する
 *
 * @tparam T パーティクル情報の型
 * 
 * @param particleList パーティクル情報のリスト
 * @param target	   カメラの注視点座標
 * @param cameraPos	   カメラの座標
 *
 * @return なし
 */
//template<typename T>
//inline void ParticleControl::CreateVertex(const std::list<T>& particleList, const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos)
//{
//	//	ビルボード設定時にもらったカメラ情報から、視線ベクトルを計算する
//	DirectX::SimpleMath::Vector3 cameraDir = target - cameraPos;
//	//	視線ベクトルは正規化しておく
//	cameraDir.Normalize();
//
//	//	パーティクル情報を、カメラからの距離順でソートする
//	std::list<T> sortedList = particleList;
//	sortedList.sort(
//		//	ソート処理の基準を示す関数については、ラムダ式で指定する
//		[&](const T& lhs, const T& rhs)
//		{
//			//	カメラ正面の距離でソート
//			return cameraDir.Dot(lhs.GetPosition() - cameraPos) > cameraDir.Dot(rhs.GetPosition() - cameraPos);
//		});
//
//
//	//	表示に使う頂点リストに登録されているデータを全削除
//	m_vertices.clear();
//	//	パーティクル情報から、表示に使う頂点リストを生成する
//	for (T li : sortedList)
//	{
//		if (cameraDir.Dot(li.GetPosition() - cameraPos) < 0.0f)
//		{
//			//	内積の結果がマイナスの場合はカメラの後ろなので表示する必要なし
//			continue;
//		}
//
//		DirectX::VertexPositionColorTexture vPCT;
//		//	表示するパーティクルの中心座標のみを入れる。
//		vPCT.position = DirectX::XMFLOAT3(li.GetPosition());
//		//	テクスチャの色
//		vPCT.color = DirectX::XMFLOAT4(li.GetNowColor());
//		//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
//		//	Yは使用しないため、0.0fを入れておく
//		vPCT.textureCoordinate = DirectX::XMFLOAT2(li.GetNowScale().x, 0.0f);
//
//		//	頂点情報を1つだけ追加。
//		AddVertex(vPCT);
//	}
//
//}
