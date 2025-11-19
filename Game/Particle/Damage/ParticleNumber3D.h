/**
 * @file   ParticleNumber3D.h
 *
 * @brief  3D空間上の数字に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"
#include"../Particle.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 数字
  */
class ParticleNumber3D : public Particle
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:
	//表示する数字
	int m_number;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleNumber3D(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor,
		int num);
	//	デストラクタ
	~ParticleNumber3D();

	// 操作
public:
	//	更新
	bool Update() override;



	int GetNumber() {
		return m_number;
	};
	//　取得・設定
public:

//　内部操作
private:

};

