/**
 * @file   Shader.h
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
#include"Game/Common/Graphics.h"

class Light;
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief シェーダー
  */
class Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Light;

	};

	//	データ受け渡し用コンスタントバッファ(送信側)
	struct PointLight
	{
		DirectX::SimpleMath::Vector3 LightPosition;      // ライト位置
		float LightInvSqrRadius;  // ライトの届く距離
		DirectX::SimpleMath::Vector3 LightColor;         // ライトカラー
		float LightIntensity = 1.0f;    // ライト強度
		DirectX::SimpleMath::Vector4	Attenuation;

	};

	struct LightBuffer 
	{
		PointLight pointLights[8];
		int onLightCount;
		DirectX::SimpleMath::Vector3 dammy;

	};


	//データ受け渡し用コンスタントバッファ(送信側)
	struct UIConstBuffer
	{
		DirectX::SimpleMath::Vector2	windowSize;
		float AlphaData;
		float dammy;
	};

	//データ受け渡し用コンスタントバッファ(送信側)
	struct NumberConstBuffer
	{
		DirectX::SimpleMath::Vector2	windowSize;
		float AlphaData=0;
		float dammy=0;
	};

	//データ受け渡し用コンスタントバッファ(送信側)
	struct ParticleConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Light;

	};
	//データ受け渡し用コンスタントバッファ(送信側)
	struct FadeConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		float mode;
		float time;
		DirectX::SimpleMath::Vector2 dummy;

	};
	//データ受け渡し用コンスタントバッファ(送信側)
	struct OutlineConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		float outlineThickness;
		DirectX::SimpleMath::Vector3 dummy;
	};


	enum ShaderType 
	{
		Model, //モデルシェーダー
		UI,   //UIシェーダー
		Number2D,
		Particle,//パーティクルシェーダー
		Fade,
		Outline,
	};

// データメンバの宣言 -----------------------------------------------
private:
	// Shaderクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<Shader> s_shader;

	Graphics* m_graphics;	// グラフィックスクラスのポインタ
	//モデルシェーダーに関する変数-----------------------------------
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_modelCBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_modelInputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_modelVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_modelPS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_modelGS;

	//アイテム用ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_itemPS;
	//モデルシェーダーに関する変数-----------------------------------
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_rockCBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_rockInputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_rockVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_rockPS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_rockGS;

	//UIシェーダーに関する変数---------------------------------------
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_UICBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_UIInputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_UIVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_UIPS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_UIGS;

	//UIシェーダーに関する変数---------------------------------------
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_numberCBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_numberInputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_numberVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_numberPS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_numberGS;

	//Particleシェーダーに関する変数---------------------------------------
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_ParticleCBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_ParticleInputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_ParticleVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ParticlePS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_ParticleGS;

	//Fadeシェーダーに関する変数---------------------------------------
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_fadeCBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_fadeInputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_fadeVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_fadePS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_fadeGS;

	//Outlineシェーダーに関する変数---------------------------------------
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_outlineCBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_outlineInputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_outlineVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_outlinePS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_outlineGS;

	//ライト配列
	std::vector<Light*> m_lights;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	//	頂点情報関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> MODEL_INPUT_LAYOUT;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> UI_INPUT_LAYOUT;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> PARTICLE_INPUT_LAYOUT;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> FADE_INPUT_LAYOUT;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> OUTLINE_INPUT_LAYOUT;
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> NUMBER_INPUT_LAYOUT;
	// コンストラクタ
	Shader();
	// インスタンスをコピーすることを禁止する
	void operator=(const Shader&) = delete;
	// インスタンスをムーブすることを禁止する
	Shader& operator= (Shader&&) = delete;
	// コピーコンストラクタは禁止する
	Shader(const Shader&) = delete;
	// ムーブコンストラクタは禁止する
	Shader(Shader&&) = delete;

	// デストラクタ
	~Shader()=default;


// 操作
public:

	void Initialize();

	void Update();

	//シェーダー開始
	void StartShader(ShaderType type,ID3D11Buffer* cBuffer);

	//シェーダー終了
	void EndShader();


	void Finalize();

//　取得・設定
public:
	static  Shader* const GetInstance();

	//インプットレイアウトの取得
	ID3D11InputLayout* GetInputLayout(ShaderType type);
	//コンスタントバッファの取得
	ID3D11Buffer* GetCBuffer(ShaderType type);
	//シェーダーの取得
	//モデルの頂点シェーダ
	ID3D11VertexShader*   GetModelVS();
	ID3D11PixelShader*    GetModelPS();
	ID3D11GeometryShader* GetModelGS();

	ID3D11PixelShader*    GetItemPS();
	ID3D11PixelShader*    GetRockPS();
	//ライト登録
	void RegisterLight(Light* light);
	//ライト解除
	void UnRegisterLight();

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
	
	//モデルシェーダー設定
	void SetModelShader(ID3D11Buffer* cBuffer);
	//UIシェーダー設定
	void SetUIShader(ID3D11Buffer* cBuffer);
	//Particleシェーダー設定
	void SetParticleShader(ID3D11Buffer* cBuffer);
	//Fadeシェーダー設定
	void SetFadeShader(ID3D11Buffer* cBuffer);
	//Outlineシェーダー設定
	void SetOutlineShader(ID3D11Buffer* cBuffer);
	void SetNumber2DShader(ID3D11Buffer* cBuffer);
};

