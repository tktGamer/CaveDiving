/**
 * @file   GemManager.cpp
 *
 * @brief  宝石管理に関するソースファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付   2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "GemManager.h"
#include<fstream>
#include<sstream>
#include"Game/Factory/GemFactory.h"

// クラスの静的メンバ変数の初期化
std::unique_ptr<GemManager> GemManager::s_gemManager = nullptr;

// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
GemManager::GemManager()
	:
	m_gemList{}
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
 * @brief 宝石のポインタをランダムに取得
 *
 * @param[in] なし
 *
 * @return 宝石のポインタ
 */
const Gem* GemManager::RandomSelection()
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
* @brief 所持宝石を保存
*
* @param[in] savePath  保存するファイルパス
* @param[in] gemID　　 宝石のID
*
* @return true   成功
* @return false  失敗
*/
bool GemManager::SaveHoldGem(const std::string& savePath, const std::vector<int>& gemID)
{
	//書き込み用ファイルストリーム作成
	std::ofstream outFile(savePath);
	if (!outFile)
	{
		//ファイルが開けなかったため失敗
		return false;
	}

	for (int i = 0; i < gemID.size(); i++)
	{
		// データを書き込み
		outFile << gemID[i] << std::endl; 
	}
	//ファイルを閉じる
	outFile.close();

	//成功
	return true;
}


/**
* @brief 所持宝石を読み込み
*
* @param[in] savePath  読み込みするファイルパス
* @param[in] gemID　　 宝石のID
*
* @return true   成功
* @return false  失敗
*/
bool GemManager::LoadHoldGem(const std::string& loadPath, std::vector<int>& gemID)
{
	//宝石をID配列を初期化
	gemID.clear();

	//読み込み用ファイルストリーム作成
	std::ifstream infile(loadPath);
	if (!infile) 
	{
		//ファイルが開けなかったため失敗
		return false;
	}
	
	std::string line;
	while (std::getline(infile, line)) 
	{
		//宝石のデータ登録番号
		int id = -1;
		try 
		{
			id = std::stoi(line);
		}
		catch (std::invalid_argument) 
		{
			//データをうまく読み込めなかったら次
			continue;
		}
	
		//idと同じ番号の宝石を取得
		gemID.push_back(id);
	
	}
	
	infile.close();
	
	return true;
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
 * @brief id番の宝石を取得
 *
 * @param[in] id 番号
 *
 * @return id番の宝石ポインタ
 *         なかったら nullptr
 */
const Gem* GemManager::GetIDNumberedGem(const int& id)
{
	//リストを順番に調べる
	for (std::unique_ptr<Gem>& gem : m_gemList) 
	{
		//引数と同じIDか
		if (gem->GetAbility().id == id) 
		{
			return gem.get();
		}
	}

	//見つからなかったらnullptr
	return nullptr;
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
	// パスの生成
	std::string path = "Resources/Data/GemData.csv";

	// ファイルのオープン
	std::ifstream ifs{ path };
	if (!ifs.is_open()) {
		// 読み込み失敗
		return;
	}

	// 1行目（ヘッダー）をスキップ
	ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// CSV読み込みループ
	while (true)
	{
		GemData gemData;
		std::string line;

		// 1行まるごと取得
		if (!std::getline(ifs, line))
			break; // ファイルの終わり

		if (line.empty())
			continue;

		std::stringstream ss(line);
		std::string token;

		// ID
		std::getline(ss, token, ',');
		gemData.id = std::stoi(token);
		if (gemData.id <= 0)
			continue;

		// 宝石の種類
		std::getline(ss, gemData.type, ',');

		// 強化項目
		std::getline(ss, gemData.item, ',');

		// 効果値
		std::getline(ss, token, ',');
		if (token != "")
		gemData.effect = std::stoi(token);

		//// 効果タイプ（空欄OK）
		//std::getline(ss, gemData.effectType, ',');

		//// 条件（空欄OK）
		//std::getline(ss, gemData.condition, ',');

		// 間隔（空欄OK）
		std::getline(ss, token, ',');
		if(token !="")
		gemData.interval = std::stoi(token);

		//// 持続時間（空欄OK）
		//std::getline(ss, gemData.duration, ',');

		// 効果説明
		std::getline(ss, gemData.description, ',');

		//生成するクラス
		std::getline(ss, token, ',');


		// 画像パス（最後の列）
		std::getline(ss, gemData.gem, '\n');

		// ====== Gem生成 ====== //
		Gem::GemAbility ability = {
			gemData.id,
			gemData.type,
			DecisinType(gemData.item),
			gemData.effect,
			gemData.interval,
		};

		const wchar_t* gemPath = TKTLib::StringToWchar(gemData.gem);
		Gem::GemImagePath imagePath = { gemPath };

		m_gemList.emplace_back(GemFactory::Instance().CreateGem(token,ability,imagePath));
	}

	ifs.close();
}