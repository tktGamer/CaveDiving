/**
 * @file   Transitor.h
 *
 * @brief  トランジションに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"


// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief トランジション
  */
class Transitor
{
// クラス定数の宣言 -------------------------------------------------
private:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		float mode =0.0f;
		float time =0.0f;
		DirectX::SimpleMath::Vector2 dummy;

	};

	
// データメンバの宣言 -----------------------------------------------
private:
	

	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;


	//	頂点情報のリスト
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;

	float m_time;

	bool m_isIn;
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	Transitor();
	~Transitor();
	// 操作
public:


	void Update();

	void Render();

	
//　取得・設定
public:
	

private:

};
