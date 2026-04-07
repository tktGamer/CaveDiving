/**
 * @file   ParticleItemGetControl.h
 *
 * @brief  パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/27
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"../ItemGet/ParticleItemGet.h"
#include"../ParticleControl.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleItemGetControl :public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//　コンストラクタ
	ParticleItemGetControl(const wchar_t* texturePath);
	//デストラクタ
	~ParticleItemGetControl();
// 操作
	//更新
	void Update();
	//描画
	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);
	//パーティクルのリクエスト
	void RequestItemGetParticle(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		const DirectX::SimpleMath::Vector3& targetPos,//向かっていくオブジェクトの位置
		const DirectX::SimpleMath::Color& color
		);
	//リセット
	void Reset();
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:
};
