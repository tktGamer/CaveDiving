/**
 * @file   ParticleDamageControl.h
 *
 * @brief  パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

#include"../ParticleControl.h"
#include"../Damage/ParticleDamageNumber.h"

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleDamageControl
{
// クラス定数の宣言 -------------------------------------------------
private:
public:

// データメンバの宣言 -----------------------------------------------
private:



	// テクスチャハンドル
	std::string m_texture;


	//	パーティクルに使う情報を保存するためのクラスオブジェクト用リスト
	std::list<std::unique_ptr<ParticleDamageNumber>> m_particleDamage;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticleDamageControl(const wchar_t* texturePath);
	~ParticleDamageControl();
	// 操作
public:


	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);

	void RequestParticleDamage(
		const DirectX::SimpleMath::Vector3& pos,//パーティクルの発生位置
		const DirectX::SimpleMath::Vector3& randomRange,
		int damage
		);
	
	void Reset();
//　取得・設定
public:

private:

};
