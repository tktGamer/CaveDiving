/**
 * @file   Light.h
 *
 * @brief  ライトに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/25
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Shader/Model/ModelShader.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ライト
  */
class Light
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//ライトが点いているか
	bool IsOn()const;
	//ライトのデータを取得
	const ModelShader::PointLightCB& GetLightData();
	//ライトのデータを設定
	void SetLightData(const ModelShader::PointLightCB& lightData);
	//ライトの色を設定
	void SetLightColor(const DirectX::SimpleMath::Vector3& color);
// コンストラクタ/デストラクタ
	// コンストラクタ
	Light();
	// デストラクタ
	~Light();
// 操作
	//初期化
	void Initialize();
	//更新
	void Update(const DirectX::SimpleMath::Vector3& positon);
	//終了
	void Finalize();
	//ライトを点ける
	void LightOn();
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//ライト情報
	ModelShader::PointLightCB  m_pointLight;
	//ライトのオンオフ状態
	bool m_isOn;
	//ライトの色
	DirectX::SimpleMath::Vector3 m_color;
};