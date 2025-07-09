/**
 * @file   GemManager.cpp
 *
 * @brief  ＸＸＸＸに関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GemManager.h"

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GemManager::GemManager()
	:m_graphics{Graphics::GetInstance()}
{

}



/**
 * @brief デストラクタ
 */
GemManager::~GemManager()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemManager::Initialize()
{
	LoadGemData();
}



/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemManager::Update()
{

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemManager::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();
}



/**
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemManager::Finalize()
{

}

/**
 * @brief 宝石の種類を決定する
 *
 * @param[in] type 宝石の種類
 *
 * @return 宝石の種類
 */
Gem::Type GemManager::DecisinType(const std::string& type)
{
	if (type == "体力")
	{
		return Gem::Type::HP;
	}
	else if (type == "攻撃力")
	{
		return Gem::Type::STR;
	}
	else if (type == "防御力")
	{
		return Gem::Type::DEF;
	}
	return  Gem::Type::UNIQUE;
}

/**
 * @brief 宝石データの読み込み
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemManager::LoadGemData()
{
	//パスの生成
	std::string path = "Resources/Data/GemData.csv";
	//ファイルのオープン
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		//読み込み失敗
		return;
	}

	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	while (true)
	{
		GemData gemData;
		std::string line;

		ifs >> gemData.id; //ID
		ifs.ignore(); //カンマを読み飛ばす
		if (gemData.id <= 0)
		{
			//IDが不正な場合は読み飛ばす
			ifs.close();
			return;
		}
		//宝石の種類を読み込む
		std::getline(ifs, line, ',');
		gemData.type = line;
		//強化項目を読み込む
		std::getline(ifs, line, ',');
		gemData.item = line;
		//効果を読み込む
		ifs >> gemData.effect;
		ifs.ignore();

		std::getline(ifs, gemData.description, '\n'); //説明文を読み込む

		//宝石データを作成
		m_gemList.emplace_back(std::make_unique<Gem>(DecisinType(gemData.item), gemData.effect, gemData.description));
	}
	ifs.close();
	return;


}
