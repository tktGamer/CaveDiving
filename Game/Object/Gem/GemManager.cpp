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


// クラスの静的メンバ変数の初期化
std::unique_ptr<GemManager> GemManager::s_gemManager = nullptr;

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
 * @brief インスタンスの取得
 *
 * @param[in] なし
 *
 * @return 　宝石マネージャーのポインタ
 */
GemManager* const GemManager::GetInstance()
{

	if (s_gemManager == nullptr)
	{
		//GemManagerオブジェクトを生成し、そのポインタをs_gemManagerに格納する
		s_gemManager.reset(new GemManager());
	}
	return s_gemManager.get();
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
 * @brief 終了処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void GemManager::Finalize()
{

}

Gem* GemManager::RandomSelection()
{
	if (m_gemList.empty()) 
	{
		return nullptr;
	}
	//ランダムに宝石を選択
	//要素の最大数
	int maxIndex = m_gemList.size() - 1;
	//ランダムな要素
	int randomIndex = TKTLib::GetRand(0, maxIndex);

	return m_gemList[randomIndex].get();
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

		//説明文を読み込む
		std::getline(ifs, gemData.description, ','); 
		//画像パスを読み込む
		std::getline(ifs, gemData.gem, '\n'); 

		Gem::GemAbility ability = { DecisinType(gemData.item), gemData.effect, gemData.description };
		const wchar_t* gemPath = TKTLib::StringToWchar(gemData.gem);
		Gem::GemImagePath imagePath = { gemPath};
		//宝石データを作成
		m_gemList.emplace_back(std::make_unique<Gem>(ability,imagePath));
	}
	ifs.close();
	return;


}
