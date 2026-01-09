/**
 * @file   Shader.h
 *
 * @brief  シェーダーの基底クラスに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/12/10
 */

 // 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include"Game/Common/Graphics.h"


// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief シェーダー基底
  */
class Shader
{
// クラス定数の宣言 -------------------------------------------------
public:
	
	struct ShaderPath
	{
		const wchar_t* vsPath;
		const wchar_t* psPath;
		const wchar_t* gsPath;
	};

// データメンバの宣言 -----------------------------------------------
private:
	
	//コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_constantBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;


// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Shader();

	// デストラクタ
	virtual ~Shader();


// 操作
public:

	//シェーダー開始
	virtual void StartShader();

	//シェーダーの終了
	void EndShader(const std::function<void()>& customState = nullptr );

//　取得・設定
public:

	//インプットレイアウトの取得
	ID3D11InputLayout* GetInputLayout();
	//コンスタントバッファの取得
	ID3D11Buffer* GetConstantBuffer();
	//シェーダーの取得
	ID3D11VertexShader*   GetVertexShader();
	ID3D11PixelShader*    GetPixelShader();
	ID3D11GeometryShader* GetGeometryShader();



	//シェーダーの作成
	void CreateShader(const wchar_t* vsPath, const wchar_t* psPath, const wchar_t* gsPath);
	//インプットレイアウトの作成
	void CreateInputLayput(const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const wchar_t* vsPath);
	//コンスタントバッファの作成
	template<typename T>
	void CreateConstantBuffer(D3D11_USAGE usage= D3D11_USAGE_DEFAULT,UINT byteWidth=sizeof(T),
							  UINT bindFlags= D3D11_BIND_CONSTANT_BUFFER,UINT CPUAccessFlags=0);
//　内部操作
private:
};



/**
 * @brief コンスタントバッファの作成
 *
 * @param[in]　usage			
 * @param[in]　byteWidth		
 * @param[in]　bindFlags
 * @param[in]　CPUAccessFlags
 *
 * @return なし
 */
template<typename T>
inline void Shader::CreateConstantBuffer(D3D11_USAGE usage, UINT byteWidth, UINT bindFlags, UINT CPUAccessFlags)
{
	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = usage;
	bd.ByteWidth = byteWidth;
	bd.BindFlags = bindFlags;
	bd.CPUAccessFlags = CPUAccessFlags;
	Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_constantBuffer);

}
