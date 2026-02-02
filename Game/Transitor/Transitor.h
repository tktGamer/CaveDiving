/**
 * @file   Transitor.h
 *
 * @brief  トランジションに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include <PrimitiveBatch.h>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief トランジション
  */
class Transitor
{
// クラス定数の宣言 -------------------------------------------------
public:
// 非公開定数
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
	// トランジション時間
	static constexpr float TRANSITION_TIME = 1.5f;
// データメンバの宣言 -----------------------------------------------
private:
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	頂点情報のリスト
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	//経過時間
	float m_time;
	//トランジションの種類
	bool m_isIn;
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	Transitor(bool isIn);
	// デストラクタ
	~Transitor();
// 操作
public:
	//再スタート
	void ReStart(bool isIn);
	//更新
	bool Update();
	//描画
	void Render();	
//　内部操作
private:

};
