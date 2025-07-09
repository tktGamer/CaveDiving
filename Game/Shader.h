/**
 * @file   Shader.h
 *
 * @brief  Shaderに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"

class Light;
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief Shader
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
	struct LightBuffer
	{
		DirectX::SimpleMath::Vector3 LightPosition;      // ライト位置
		float LightInvSqrRadius;  // ライトの届く距離
		DirectX::SimpleMath::Vector3 LightColor;         // ライトカラー
		float LightIntensity;    // ライト強度
		DirectX::SimpleMath::Vector4	Attenuation;

	};

	enum ShaderType 
	{
		Model, //モデルシェーダー
		UI,   //UIシェーダー
	};

// データメンバの宣言 -----------------------------------------------
private:
	// Shaderクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<Shader> s_shader;

	Graphics* m_graphics;	// グラフィックスクラスのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_modelVS;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_modelPS;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_modelGS;

	//ライト配列
	std::vector<Light*> m_lights;
	//	関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
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

	void Draw();

	void Finalize();

//　取得・設定
public:
	static  Shader* const GetInstance();

	ID3D11InputLayout* GetInputLayout();
	//シェーダーの取得
	//モデルの頂点シェーダ
	ID3D11VertexShader*   GetModelVS();
	ID3D11PixelShader*    GetModelPS();
	ID3D11GeometryShader* GetModelGS();

	//ライト登録
	void RegisterLight(Light* light);
//　内部操作
private:
	//シェーダ作成
	void CreateShader();

	//モデルシェーダー設定
	void SetModelShader(ID3D11Buffer* cBuffer);
};

