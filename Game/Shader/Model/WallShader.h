/**
 * @file   WallShader.h
 *
 * @brief  壁モデル用シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　22025/10/24
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
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

	//	データ受け渡し用コンスタントバッファ(送信側)
	struct CameraToPlayerCB
	{
		DirectX::SimpleMath::Vector3 cameraPos;
		float fadeRadius=0;
		DirectX::SimpleMath::Vector3 playerPos;
		float fadestrength=0;//0.0f-1.0f

	};


// データメンバの宣言 -----------------------------------------------
private:

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cameraToPlayerCB;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	WallShader(const ShaderPath& pathes);

	// デストラクタ
	~WallShader();


// 操作
public:
	void StartShader(const CameraToPlayerCB& cb);
//　取得・設定
public:

//　内部操作
private:
	
};

