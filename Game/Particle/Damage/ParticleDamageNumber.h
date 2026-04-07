/**
 * @file   ParticleDamageNumber.h
 *
 * @brief  ダメージ数値パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/26
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../ParticleControl.h"
#include"../Damage/ParticleNumber3D.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ダメージ数値パーティクル
  */
class ParticleDamageNumber : public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:
private:
	//速度
	static constexpr DirectX::SimpleMath::Vector3 VELOCITY = { 0.0f,2.5f,0.0f };
	//加速度
	static constexpr DirectX::SimpleMath::Vector3 ACCELE = { 0.0f,-3.0f,0.0f };

// メンバ関数の宣言 -------------------------------------------------
//取得・設定
public:
	//削除するか
	bool IsDelete();
// コンストラクタ/デストラクタ
	//	コンストラクタ（初期設定）
	ParticleDamageNumber(
		const wchar_t* texturePsth,
		const DirectX::SimpleMath::Vector3& pos,
		const int& number);
	//	デストラクタ
	~ParticleDamageNumber();
// 操作
	//	更新
	void Update();
	//	描画
	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);
	//	リセット
	void Reset();
//内部処理
private:
	//桁数カウント
	int CheckDigit(const int& num);
	//ビルボード
	void CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up);
// データメンバの宣言 -----------------------------------------------
private:
	//数字の基準位置	
	DirectX::SimpleMath::Vector3 m_basePosition;
	//ビルボード
	DirectX::SimpleMath::Matrix m_billboard;
};