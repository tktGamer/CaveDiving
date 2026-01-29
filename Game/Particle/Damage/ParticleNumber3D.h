/**
 * @file   ParticleNumber3D.h
 *
 * @brief  3D空間上の数字に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔　
 *
 * @date   日付　2026/01/26
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

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//	コンストラクタ（初期設定）
	ParticleNumber3D(
		float life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale, const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor,const DirectX::SimpleMath::Color& endColor,
		int num);
	//	デストラクタ
	~ParticleNumber3D();
// 操作
	//	更新
	bool Update() override;
	//数字を取得
	int GetNumber() const {return m_number;};
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//表示する数字
	int m_number;
};