/**
 * @file   ShaderManager.h
 *
 * @brief  シェーダーに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　22025/10/24
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

class Light;
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief シェーダー
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
	};


// データメンバの宣言 -----------------------------------------------
private:
	// Shaderクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<ShaderManager> s_shader;

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


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	
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

	// デストラクタ
	~ShaderManager()=default;


// 操作
public:

	void Initialize();

	void Update();

	//シェーダー開始
	void StartShader(const ShaderType& type);

	//シェーダー終了
	void EndShader();


	void Finalize();

//　取得・設定
public:
	static  ShaderManager* const GetInstance();

	//カメラとプレイヤーの位置情報バッファ設定
	void SetCameraToPlayerCB(const WallShader::CameraToPlayerCB& cameraToPlayerCB);
	//カメラ情報バッファ設定
	void SetCameraCB(const ParticleShader::CameraCB& cameraCB);

	//インプットレイアウトの取得
	ID3D11InputLayout* GetInputLayout(ShaderType type);
	//コンスタントバッファの取得
	ID3D11Buffer* GetCBuffer(ShaderType type);
	

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
	
	//モデルシェーダー設定
	void SetModelShader();
	void SetItemShader();
	void SetRockShader();
	void SetWallShader();
	//UIシェーダー設定
	void SetUIShader();
	//Particleシェーダー設定
	void SetParticleShader();
	//Fadeシェーダー設定
	void SetFadeShader();
	//Outlineシェーダー設定
	void SetOutlineShader();
	void SetNumber2DShader();
	void SetNumber3DShader();
};

