/**
 * @file   ParticleDamageNumber.h
 *
 * @brief  ダメージ数値パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2025//11/25
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"../ParticleControl.h"
#include"../Damage/ParticleNumber3D.h"



// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleDamageNumber : public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:


// データメンバの宣言 -----------------------------------------------
private:

	//数字の基準位置	
	DirectX::SimpleMath::Vector3 m_basePosition;
	//ビルボード
	DirectX::SimpleMath::Matrix m_billboard;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleDamageNumber(
		const std::string& texturePsth,
		const DirectX::SimpleMath::Vector3& pos,
		const int& number);
	//	デストラクタ
	~ParticleDamageNumber();

// 操作
public:
	//	更新
	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);

	void Reset();

	//取得・設定
public:
	//削除するか
	bool IsDelete();
//内部処理
private:
	//桁数カウント
	int CheckDigit(const int& num);

	//ビルボード
	void CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up);

};

