/**
 * @file   ParticleShieldControl.h
 *
 * @brief  盾パーティクル管理に関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/01/28
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../ParticleControl.h"
#include"../Shield/ParticleShield.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 盾パーティクル管理
  */
class ParticleShieldControl : public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//コンストラクタ
	ParticleShieldControl(const wchar_t* texturePath);
	//デストラクタ
	~ParticleShieldControl();
// 操作
	//更新
	void Update();
	//描画
	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);
	//盾パーティクル要求
	void RequestParticleShield(
		const int& objectID//パーティクルの発生位置
		);
	//リセット
	void Reset();
	//消去
	void Delete();
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
};
