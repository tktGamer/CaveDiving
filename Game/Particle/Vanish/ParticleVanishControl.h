/**
 * @file   ParticleVanishControl.h
 *
 * @brief  消滅パーティクルのコントローラに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付  2026/01/28
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include <list>
#include"../Vanish/ParticleVanish.h"
#include"../ParticleControl.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 消滅パーティクルのコントローラ
  */
class ParticleVanishControl :public ParticleControl
{
// クラス定数の宣言 -------------------------------------------------
public:
//非公開定数
private:
	// 消滅パーティクルの数
	static constexpr int VANISH_PARTICLE_NUM = 14; 
	//最初に生成する数
	static constexpr int INIT_GENERATE_NUM = 6;
	//パーティクルの生存時間
	static constexpr float PARTICLE_LIFE = 0.2f;
	//生成したパーティクルの進む方向
	static constexpr DirectX::SimpleMath::Vector3 VANISH_PARTICLE_DIRECTION[VANISH_PARTICLE_NUM] =
	{
		{  0.0f,  1.0f,  0.0f }, // 上
		{  0.0f, -1.0f,  0.0f }, // 下
		{  1.0f,  0.0f,  0.0f }, // 右
		{  0.0f,  0.0f,  1.0f }, // 前
		{ -1.0f,  0.0f,  0.0f }, // 左
		{  0.0f,  0.0f, -1.0f }, // 後ろ
		{ -1.0f, -1.0f, -1.0f }, // 左下後ろ
		{ -1.0f, -1.0f,  1.0f }, // 左下前
		{ -1.0f,  1.0f, -1.0f }, // 左上後ろ
		{ -1.0f,  1.0f,  1.0f }, // 左上前
		{  1.0f, -1.0f, -1.0f }, // 右下後ろ
		{  1.0f, -1.0f,  1.0f }, // 右下前
		{  1.0f,  1.0f, -1.0f }, // 右上後ろ
		{  1.0f,  1.0f,  1.0f }  // 右上前
	};
	//速度
	static constexpr float PARTICLE_SPEED = 7.0f;
	//加速度
	static constexpr DirectX::SimpleMath::Vector3 PARTICLE_ADD_VELOCITY = { -0.4f,-0.4f,-0.4f };
	//初期サイズ
	static constexpr DirectX::SimpleMath::Vector3 PARTICLE_START_SIZE = { 0.1f,0.1f,0.1f };
	//最終サイズ
	static constexpr DirectX::SimpleMath::Vector3 PARTICLE_END_SIZE = {		0.5f,	0.5f,	0.5f };

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
	//コンストラクタ
	ParticleVanishControl(const wchar_t* texturePath);
	//デストラクタ
	~ParticleVanishControl();
// 操作
	//更新
	void Update();
	//描画
	void Render(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& cameraPos, const DirectX::SimpleMath::Vector3& cameraUp);
	//消滅パーティクル生成
	void RequestVanishParticle(
		const DirectX::SimpleMath::Vector3& pos//パーティクルの発生位置
		);
	//リセット
	void Reset();
//内部処理
private:

// データメンバの宣言 -----------------------------------------------
private:

};