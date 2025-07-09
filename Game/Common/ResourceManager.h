#pragma once
// ヘッダファイルの読み込み ===================================================
#include<unordered_map>
#include<string>
#include"Game/Common/Graphics.h"
#include"Game/Common/BinaryFile.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief リソースの管理
  */
class ResourceManager
{
//エイリアス宣言
private:                                        //ファイル名　ハンドル
	using TextureResource    = std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;
	using SoundResouce		 = std::unordered_map<std::string, std::unique_ptr<DirectX::SoundEffect>>;
	using ModelResouce		 = std::unordered_map<std::string, std::unique_ptr<DirectX::Model>>;
	using BinaryResouce		 = std::unordered_map<std::string, std::unique_ptr<BinaryFile>>;
// クラス定数の宣言 -------------------------------------------------
public:
	static constexpr  char const* DEFAULT_TEXTURE_DIRECTORY		= "Resources/Textures/";
	static constexpr  char const* DEFAULT_SOUND_DIRECTORY		= "Resources/Sounds/";
	static constexpr  char const* DEFAULT_MODELS_DIRECTORY		= "Resources/Models/";


// データメンバの宣言 -----------------------------------------------
private:
	// ResourceManagerクラスのインスタンスへのユニークポインタ「シングルトン化する」
	static std::unique_ptr<ResourceManager> s_resourceManager;

	DirectX::AudioEngine* m_audioEngine;

	//画像データ群
	TextureResource m_texture;
	//音データ群
	SoundResouce m_sounds;
	//モデルデータ群
	ModelResouce m_models;

	// バイナリファイル
	BinaryResouce m_binaryFile; 
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	ResourceManager();
	// インスタンスをコピーすることを禁止する
	void operator=(const ResourceManager&) = delete;
	// インスタンスをムーブすることを禁止する
	ResourceManager& operator= (ResourceManager&&) = delete;
	// コピーコンストラクタは禁止する
	ResourceManager(const ResourceManager&) = delete;
	// ムーブコンストラクタは禁止する
	ResourceManager(ResourceManager&&) = delete;

	// デストラクタ
	~ResourceManager();


// 操作
public:
	// ResourceManagerクラスのインスタンスを取得する
	static ResourceManager* const GetInstance();

	//画像データ要求
	ID3D11ShaderResourceView** RequestTexture(wchar_t const*     filename);
	ID3D11ShaderResourceView** RequestTexture(const std::string& filename);

	//音データ要求
	DirectX::SoundEffect* RequestSound(wchar_t const*     filename);
	DirectX::SoundEffect* RequestSound(const std::string& filename);

	//sdkmeshモデルデータ要求
	DirectX::Model* RequestModel(wchar_t const*     filename);
	DirectX::Model* RequestModel(const std::string& filename);

	//バイナリファイル要求
	BinaryFile* RequestBinaryFile(wchar_t const* filename);
	//全リソース削除
	void Clear();

//内部操作
private:
	//skdmeshモデルデータ読み込み
	void LoadModel(const std::string& filename);
	//wav音データ読み込み
	void LoadSound(const std::string& filename);
	//画像データ読み込み
	void LoadTexture(const std::string& filename);

	//全リソースの読み込み
	void LoadResources();
	//取得・設定
public:
	void SetAudioEngine(DirectX::AudioEngine* audioEngine) { m_audioEngine = audioEngine; }
};
