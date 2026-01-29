/**
 * @file   WallShader.h
 *
 * @brief  壁モデル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../Model/ModelShader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 壁モデルシェーダー
  */
class WallShader : public ModelShader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	カメラとプレイヤーの情報用コンスタントバッファ(送信側)
	struct CameraToPlayerCB
	{
		//カメラ位置
		DirectX::SimpleMath::Vector3 cameraPos;
		//透過する大きさ
		float fadeRadius=0;
		//プレイヤーの位置
		DirectX::SimpleMath::Vector3 playerPos;
		//透過度
		float fadestrength=0;//0.0f-1.0f

	};
// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	// コンストラクタ
	WallShader(const ShaderPath& pathes);
	// デストラクタ
	~WallShader();
// 操作
	//シェーダー開始
	void StartShader(const CameraToPlayerCB& cb);
//　内部操作
private:
	
// データメンバの宣言 -----------------------------------------------
private:
	//CameraToPlayerCB用バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cameraToPlayerCB;
};

