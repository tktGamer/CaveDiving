/**
 * @file   ShaderManager.h
 *
 * @brief  シェーダー管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/29
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include<unordered_map>
#include"../Shader/Model/ModelShader.h"
#include"../Shader/Model/WallShader.h"
#include"../Shader/UI/UIShader.h"
#include"../Shader/Fade/FadeShader.h"
#include"../Shader/Number/Number2DShader.h"
#include"../Shader/Number/Number3DShader.h"
#include"../Shader/Outline/OutlineShader.h"
#include"../Shader/Particle/ParticleShader.h"
#include"../Shader/Animation2D/Animation2DShader.h"
// クラスの宣言 ===============================================================
class Light;
// クラスの定義 ===============================================================
/**
  * @brief シェーダー管理
  */
class ShaderManager
{
// クラス定数の宣言 -------------------------------------------------
public:

	enum ShaderType 
	{
		Model, //モデルシェーダー
		Item_Model,
		Rock_Model,
		Wall_Model,
		UI,   //UIシェーダー
		Number2D,
		Number3D,
		Particle,//パーティクルシェーダー
		Fade,
		Outline,
		Animation2D
	};


// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
	//インスタンスを取得
	static  ShaderManager* const GetInstance();
	//カメラとプレイヤーの位置情報バッファ設定
	void SetCameraToPlayerCB(const WallShader::CameraToPlayerCB& cameraToPlayerCB);
	//カメラ情報バッファ設定
	void SetCameraCB(const ParticleShader::CameraCB& cameraCB);
	//インプットレイアウトの取得
	ID3D11InputLayout* GetInputLayout(ShaderType type);
	//コンスタントバッファの取得
	ID3D11Buffer* GetCBuffer(ShaderType type);
//　デストラクタ
public:
	// デストラクタ
	~ShaderManager()=default;
// 操作
public:
	//シェーダー開始
	void StartShader(const ShaderType& type);
	//シェーダー終了
	void EndShader();
	//終了
	void Finalize();
// コンストラクタ
private:
	// コンストラクタ
	ShaderManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const ShaderManager&) = delete;
	// インスタンスをムーブすることを禁止する
	ShaderManager& operator= (ShaderManager&&) = delete;
	// コピーコンストラクタは禁止する
	ShaderManager(const ShaderManager&) = delete;
	// ムーブコンストラクタは禁止する
	ShaderManager(ShaderManager&&) = delete;
//　内部操作
private:
	//シェーダ作成
	void CreateShader();
	//モデルシェーダー読み込み
	void LoadModelShader();
	//UIシェーダー読み込み
	void LoadUIShader();
	//Particleシェーダー読み込み
	void LoadParticleShader();
	//Fadeシェーダー読み込み
	void LoadFadeShader();
	//Outlineシェーダー読み込み
	void LoadOutlineShader();
	//Number2Dシェーダー読み込み
	void LoadNumber2DShader();
	//Number2Dシェーダー読み込み
	void LoadNumber3DShader();
	//シェーダー読み込み
	void LoadAnimation2DShader();

	//モデルシェーダー設定
	void SetModelShader();
	//アイテムシェーダー設定
	void SetItemShader();
	//岩シェーダー設定
	void SetRockShader();
	//壁シェーダー設定
	void SetWallShader();
	//UIシェーダー設定
	void SetUIShader();
	//Particleシェーダー設定
	void SetParticleShader();
	//Fadeシェーダー設定
	void SetFadeShader();
	//Outlineシェーダー設定
	void SetOutlineShader();
	//数字用シェーダー設定
	void SetNumber2DShader();
	//3D数字用シェーダー設定
	void SetNumber3DShader();
	//２Dアニメーション設定
	void SetAnimation2DShader();

// データメンバの宣言 -----------------------------------------------
private:
	// ShaderManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<ShaderManager> s_shader;
	//種類に対応したシェーダマップ
	std::unordered_map<ShaderType, Shader*>  m_shaderMap;
	
	//モデル用シェーダー
	std::unique_ptr<ModelShader> m_modelShader;
	//アイテム用シェーダー
	std::unique_ptr<ModelShader> m_itemShader;
	//岩用シェーダー
	std::unique_ptr<ModelShader> m_rockShader;
	//カメラとプレイヤーの位置情報バッファ
	WallShader::CameraToPlayerCB m_cameraToPlayerCB;
	//壁用シェーダー
	std::unique_ptr<WallShader> m_wallShader;
	//UI用シェーダー
	std::unique_ptr<UIShader> m_uiShader;
	//2D上の数字用シェーダー
	std::unique_ptr<Number2DShader> m_number2DShader;
	//カメラ情報バッファ
	ParticleShader::CameraCB m_cameraCB;
	//3D空間上の数字用シェーダー
	std::unique_ptr<ParticleShader> m_number3DShader;
	//パーティクルエフェクト用シェーダー
	std::unique_ptr<ParticleShader> m_particleShader;
	//フェイド用シェーダー
	std::unique_ptr<FadeShader> m_fadeShader;
	//アウトライン用シェーダー
	std::unique_ptr<OutlineShader> m_outlineShader;
	//２Dアニメーション用シェーダー
	std::unique_ptr<Animation2DShader> m_animation2DShader;

};

