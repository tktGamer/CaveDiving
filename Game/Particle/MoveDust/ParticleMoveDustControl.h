/**
 * @file   ParticleMoveDustControl.h
 *
 * @brief  歩行パーティクルに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include <list>


#include"../MoveDust/ParticleMoveDust.h"
#include"../ParticleControl.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief パーティクル
  */
class ParticleMoveDustControl :public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	ParticleMoveDustControl(const wchar_t* texturePath);
	~ParticleMoveDustControl();
	// 操作
public:


	void Update();

	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);


	void RequestMoveDustParticle(
		DirectX::SimpleMath::Vector3 pos//パーティクルの発生位置
		);
	
	void Reset();
//　取得・設定
public:

private:

};
