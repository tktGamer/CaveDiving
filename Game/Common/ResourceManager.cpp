// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "ResourceManager.h"

using namespace DirectX;

// クラスの静的メンバ変数の初期化
std::unique_ptr<ResourceManager> ResourceManager::s_resourceManager = nullptr;

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
ResourceManager::ResourceManager()
	:m_texture{}
	,m_sounds{}
	,m_models{}
	, m_audioEngine{ nullptr }
{
}


/**
 * @brief デストラクタ
 */
ResourceManager::~ResourceManager()
{
	//全リソースの削除
	Clear();
}



/**
 * @brief インスタンスの取得
 *
 * @param[in] なし
 *
 * @return 　リソースマネージャーのポインタ
 */
ResourceManager* const ResourceManager::GetInstance()
{
	
	if (s_resourceManager == nullptr)
	{
		//ResourceManagerオブジェクトを生成し、そのポインタをs_resourceManagerに格納する
		s_resourceManager.reset(new ResourceManager());
	}
	return s_resourceManager.get();
}

/**
 * @brief 画像データの要求
 *
 * @param[in] filename 画像ファイル名
 *
 * @return 　画像データのハンドル
 */
ID3D11ShaderResourceView** ResourceManager::RequestTexture(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);
	//未登録の場合
	if (m_texture.count(stringFilename) == 0)
	{
		LoadTexture(stringFilename);

	}

	//登録してある画像データのハンドルを返却
	return m_texture[stringFilename].GetAddressOf();
}
ID3D11ShaderResourceView** ResourceManager::RequestTexture(const std::string& filename)
{
	//未登録の場合
	if (m_texture.count(filename) == 0)
	{
		LoadTexture(filename);

	}

	////登録してある画像データのハンドルを返却
	return m_texture[filename].GetAddressOf();

}

/**
 * @brief 音データの要求
 *
 * @param[in] filename 音ファイル名
 *
 * @return 音データのポインタ
 */
DirectX::SoundEffect* ResourceManager::RequestSound(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);
	//未登録の場合
	if (m_sounds.count(stringFilename) == 0)
	{
		//wav音ファイルの読み込み
		LoadSound(stringFilename);
	}

	//登録してある画像データのハンドルを返却
	return m_sounds[stringFilename].get();
}
DirectX::SoundEffect* ResourceManager::RequestSound(const std::string& filename)
{
	//未登録の場合
	if (m_sounds.count(filename) == 0)
	{
		//wav音ファイルの読み込み
		LoadSound(filename);
	}

	//登録してある画像データのハンドルを返却
	return m_sounds[filename].get();
}

/**
 * @brief モデルデータの要求
 *
 * @param[in] filename モデルデータファイル名
 *
 * @return  モデルデータのポインタ
 */
DirectX::Model* ResourceManager::RequestModel(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);

	//未登録の場合
	if (m_models.count(stringFilename) == 0) 
	{
		//sdkmeshモデルデータの読み込み
		LoadModel(stringFilename);
	}

	return m_models[stringFilename].get();
}

DirectX::Model* ResourceManager::RequestModel(const std::string& filename)
{
   // 未登録の場合
   if (m_models.count(filename) == 0) 
   {
	   //sdkmeshモデルデータの読み込み
	   LoadModel(filename);
   }

   return m_models[filename].get();
}


BinaryFile* ResourceManager::RequestBinaryFile(wchar_t const* filename)
{
	std::string stringFilename = TKTLib::WcharToString(filename);
	//未登録の場合
	if (m_binaryFile.count(stringFilename) == 0)
	{
		//バイナリファイルの読み込み
		std::unique_ptr<BinaryFile> binaryFile = std::make_unique<BinaryFile>();
		
		m_binaryFile.insert(std::make_pair(stringFilename, binaryFile->LoadFile(filename)));
	}
	return m_binaryFile[stringFilename].get();
}

/**
 * @brief データ削除
 *
 * @param[in] なし
 *
 * @return なし
 */
void ResourceManager::Clear()
{
	m_models.clear();
	m_sounds.clear();
	m_texture.clear();
}

/**
 * @brief sdkmeshモデルデータの読み込み
 *
 * @param[in] filename モデルデータファイル名
 *
 * @return  なし
 */
void ResourceManager::LoadModel(const std::string& filename)
{
	std::string fullPath = DEFAULT_MODELS_DIRECTORY + filename;
	// 例外処理対応
	try
	{
		ID3D11Device* device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
		DirectX::DX11::EffectFactory* fx = Graphics::GetInstance()->GetFX();
		fx->SetDirectory(L"Resources/Models");
		std::unique_ptr<Model> model = Model::CreateFromSDKMESH(device,TKTLib::StringToWchar(fullPath), *fx);
		m_models.insert(std::make_pair(filename, std::move(model)));
	}
	catch (const std::exception& e)
	{
		e;
		//エラーメッセージの表示
		TKTLib::ShowErrorMessage(filename, fullPath,TKTLib::ErrorType::FileNotFound);
	}
	catch (...)
	{

		MessageBox(nullptr, L"予期せぬエラーが発生しました", L"エラー", MB_OK);
		PostQuitMessage(0);
	}

}

/**
 * @brief wav音データの読み込み
 *
 * @param[in] filename 音データファイル名
 *
 * @return  なし
 */
void ResourceManager::LoadSound(const std::string& filename)
{
	std::string fullPath = DEFAULT_SOUND_DIRECTORY + filename;
	
	// 例外処理対応
	try
	{		
		std::unique_ptr<SoundEffect> soundEffect=std::make_unique<SoundEffect>(m_audioEngine,TKTLib::StringToWchar(fullPath));
		
		//画像データのハンドルを登録
		m_sounds.insert(std::make_pair(filename, std::move(soundEffect)));
	}
	catch (const std::exception& e)
	{
		//エラーメッセージの表示
		TKTLib::ShowErrorMessage(filename, fullPath, TKTLib::ErrorType::FileNotFound);
	}
	catch (...)
	{

		MessageBox(nullptr, L"予期せぬエラーが発生しました", L"エラー", MB_OK);
		PostQuitMessage(0);
	}

}

/**
 * @brief 画像データの読み込み
 *
 * @param[in] filename 画像データファイル名
 *
 * @return  なし
 */
void ResourceManager::LoadTexture(const std::string& filename)
{
	std::string fullPath = DEFAULT_TEXTURE_DIRECTORY + filename;
	// 例外処理対応
	try
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureHandle;
		ID3D11Device* device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
		ID3D11DeviceContext* context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
		//画像データ読み込み
		CreateWICTextureFromFile(
			device,
			context,
			TKTLib::StringToWchar(fullPath),
			nullptr,
			textureHandle.ReleaseAndGetAddressOf());
		
		if (!textureHandle)
		{
			throw std::runtime_error("ファイルが見つからなかった");
		}
		//画像データのハンドルを登録
		m_texture.insert(std::make_pair(filename, std::move(textureHandle)));
	}
	catch (const std::exception& e)
	{
		//エラーメッセージの表示
		TKTLib::ShowErrorMessage(filename, fullPath, TKTLib::ErrorType::FileNotFound);
	}
	catch (...)
	{
		MessageBox(nullptr, L"予期せぬエラーが発生しました", L"エラー", MB_OK);
		PostQuitMessage(0);
	}
}

void ResourceManager::LoadResources()
{
}
