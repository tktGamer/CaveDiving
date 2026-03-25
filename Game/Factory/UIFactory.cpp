/**
 * @file   UIFactory.cpp
 *
 * @brief  UI生成に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/01/18
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UIFactory.h"
#include"Game/UI/UIManager.h"
 // メンバ関数の定義 ===========================================================
/**
 * @brief 「UI」の生成
 *
 * @param[in] path      画像パス
 * @param[in] position  描画座標
 * @param[in] scale     拡大率
 * @param[in] anchor    アンカー
 *
 * @return 宝石選択UIクラス
 */
std::unique_ptr<UserInterface> UIFactory::CreateUserInterface(
	const wchar_t* path, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor)
{
	//「UI」の生成
	std::unique_ptr<UserInterface> ui = std::make_unique<UserInterface>();
	ui->SetWindowSize(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y);
	ui->Create(path, position, scale, anchor);
	ui->Initialize();

	return ui;
}

/**
 * @brief 「メニューUI」の生成
 *
 * @param[in] cursolSound カーソル移動時の効果音
 * @param[in] munuUIInfo  初期追加する選択肢
 *
 * @return メニューUIクラス
 */
std::unique_ptr<Menu> UIFactory::CreateMenu(DirectX::SoundEffect* cursolSound, const std::vector<Menu::MunuUIInfo>& munuUIInfo)
{
	//「メニューUI」の生成
	std::unique_ptr<Menu> menu = std::make_unique<Menu>(cursolSound);
	menu->Initialize();
	//選択しの生成
	for (auto& info : munuUIInfo)
	{
		menu->Add(info);
	}
	return menu;
}

/**
 * @brief 「ゲージUI」の生成
 *
 * @param[in] position  描画座標
 * @param[in] scale     拡大率
 * @param[in] anchor    アンカー
 * @param[in] currentValue    現在値
 * @param[in] maxValue    　　　最大値
 *
 * @return ゲージUIクラス
 */
std::unique_ptr<Gauge> UIFactory::CreateGauge(const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale,
	const UserInterface::ANCHOR& anchor, const int& currentValue, const int maxValue)
{
	//ゲージUI生成
	std::unique_ptr<Gauge> gauge = std::make_unique<Gauge>(position,scale,anchor);
	gauge->Initialize();
	//値を設定
	gauge->SetCurrentValue(currentValue);
	gauge->SetMaxValue(maxValue);
	return gauge;
}

/**
 * @brief 「クリア条件UI」の生成
 *
 * @param[in] pos  描画位置
 *
 * @return クリア条件UIクラス
 */
std::unique_ptr<ClearConditions> UIFactory::CreateClearConditions(const DirectX::SimpleMath::Vector2& pos)
{
	//クリア条件UI生成
	std::unique_ptr<ClearConditions> clearConditions = std::make_unique<ClearConditions>(pos);
	clearConditions->Initialize();

	return clearConditions;
}

/**
 * @brief 「宝石選択UI」の生成
 *
 * @param[in] pGemSelectUIManager  宝石選択UI群管理クラスポインタ
 * @param[in] gemID  宝石ID
 * 
 * @return 宝石選択UIクラス
 */
std::unique_ptr<GemSelect> UIFactory::CreateGemSelect(GemSelectUIManager* pGemSelectUIManager, const std::vector<int>& gemID)
{
	//「宝石選択UI」の生成
	std::unique_ptr<GemSelect> gemSelect = std::make_unique<GemSelect>(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y,gemID,pGemSelectUIManager );
	gemSelect->Initialize();
	return gemSelect;
}

/**
 * @brief 「入れ替え確認UI」の生成
 *
 * @param[in] pGemSelectUIManager  宝石選択UI群管理クラスポインタ
 *
 * @return 入れ替え確認UIクラス
 */
std::unique_ptr<ChangeConfirm> UIFactory::CreateChangeConfirm(GemSelectUIManager* pGemSelectUIManager)
{

	//「入れ替え確認UI」の生成
	std::unique_ptr<ChangeConfirm> changeConfirm = std::make_unique<ChangeConfirm>(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y, pGemSelectUIManager);
	changeConfirm->Initialize();

	return changeConfirm;
}

/**
 * @brief 「宝石入れ替えUI」の生成
 *
 * @param[in] pGemSelectUIManager  宝石選択UI群管理クラスポインタ
 * @param[in] gemID  宝石ID
 * 
 * @return 宝石入れ替えUIクラス
 */
std::unique_ptr<ChangeGem> UIFactory::CreateChangeGem(GemSelectUIManager* pGemSelectUIManager,const std::vector<int>& gemID)
{
	//「宝石入れ替えUI」の生成
	std::unique_ptr<ChangeGem> changeGem = std::make_unique<ChangeGem>(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y,gemID, pGemSelectUIManager);
	changeGem->Initialize();

	return changeGem;
}

/**
 * @brief 「所持している宝石を表示するUI」の生成
 *
 * @param[in] gemID  宝石ID
 * @param[in] position  描画位置
 * @param[in] scale  　 大きさ
 *
 * @return 所持している宝石を表示するUIクラス
 */
std::unique_ptr<HoldGem> UIFactory::CreateHoldGem(const std::vector<int>& gemID,
	const DirectX::SimpleMath::Vector2& position,const DirectX::SimpleMath::Vector2& scale)
{
	//「所持している宝石を表示するUI」の生成
	std::unique_ptr<HoldGem> holdGem = std::make_unique<HoldGem>(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y,position,scale);
	holdGem->Initialize();
	//表示する宝石を決める
	holdGem->ChangeDrawGem(gemID);
	return holdGem;
}

/**
 * @brief 「所持している宝石の内1つの情報を表示するUI」の生成
 *
 * @param[in] gemID  宝石ID
 * 
 * @return 所持している宝石の内1つの情報を表示するUIクラス
 */
std::unique_ptr<HoldGemInfoDraw> UIFactory::CreateHoldGemInfoDraw(const std::vector<int>& gemID)
{
	//「所持している宝石の内1つの情報を表示するUI」の生成
	std::unique_ptr<HoldGemInfoDraw> holdGemInfo = std::make_unique<HoldGemInfoDraw>(UIManager::WINDOW_SIZE_X, UIManager::WINDOW_SIZE_Y,gemID);
	holdGemInfo->Initialize();

	return holdGemInfo;
}

/**
 * @brief 「数字UI」の生成
 *
 * @param[in] data        数字画像情報
 * @param[in] pos  　　　 描画座標
 * @param[in] scale       拡大率
 * @param[in] color    　 色
 * @param[in] initNumber　初期数字
 * @param[in] minDigit    最小表示桁数
 *
 * @return 数字UIクラス
 */
std::unique_ptr<NumberControl> UIFactory::CreateNumberUI(
	const NumberControl::NumberTextureData& data, const DirectX::SimpleMath::Vector2& pos,
	const DirectX::SimpleMath::Vector2& scale, const DirectX::SimpleMath::Vector4& color,
	const int& initNumber, const int& minDigit)
{
	//「数字UI」の生成
	std::unique_ptr<NumberControl> numberControl = std::make_unique<NumberControl>(data, pos, color);
	numberControl->Initialize();
	numberControl->SetScale(scale);
	//初期数字
	numberControl->SetNumber(initNumber);
	//最小表示桁数
	numberControl->SetDrawMinDigit(minDigit);
	return numberControl;
}

/**
 * @brief 「カウント数字UI」の生成
 *
 * @param[in] numberUI      数字UI
 * @param[in] numberInfoUI  数字の意味UI
 * @param[in] initNumber    初期数字  
 * @param[in] targetNumber  目標数字
 * @param[in] stepNumber　  数字増加量
 *
 * @return カウント数字UIクラス
 */
std::unique_ptr<CountUpNumber> UIFactory::CreateCountUpNumberUI(std::unique_ptr<NumberControl> numberUI, std::unique_ptr<UserInterface> numberInfoUI
	, const int& initNumber , const int& targetNumber, const int& stepNumber)
{
	std::unique_ptr<CountUpNumber> numberControl = std::make_unique<CountUpNumber>(initNumber, targetNumber, stepNumber);
	numberControl->Initialize();
	numberControl->CreateNumberUI(std::move(numberUI));
	numberControl->CreateInfoTextureUI(std::move(numberInfoUI));
	return numberControl;
}

/**
 * @brief 「アニメーション2DUI」の生成
 *
 * @param[in] texturepath    画像パス
 * @param[in] textureInfo  　画像情報
 * @param[in] animationTime  アニメーション時間
 * @param[in] isLoop    　   アニメーションを繰り返すか
 * @param[in] position　	 座標
 * @param[in] scale			 拡大率
 *
 * @return 2Dアニメーションクラス
 */
std::unique_ptr<Animation2D> UIFactory::CreateAnimation2DUI(const wchar_t* texturepath, const Animation2D::AnimationTexture& textureInfo, 
	const float& animationTime, const bool& isLoop, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale)
{
	std::unique_ptr<Animation2D> animation2D = std::make_unique<Animation2D>(
		texturepath, textureInfo, animationTime,
		isLoop,position,scale);
	animation2D->Initialize();
	animation2D->SetWindowSize(DirectX::SimpleMath::Vector2{ static_cast<float>(UIManager::WINDOW_SIZE_X),static_cast<float>(UIManager::WINDOW_SIZE_Y) });
	return animation2D;
}

/**
 * @brief 「バフUI」の生成
 *
 * @param[in] time    表示時間
 * @param[in] path  　画像情報
 * @param[in] position　	 座標
 * @param[in] scale			 拡大率
 * @param[in] anchor		 表示基準
 *
 * @return バフUIクラス
 */
std::unique_ptr<Buff> UIFactory::CreateBuffUI(const float& time, const wchar_t* path,
	const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor)
{
	//「バフUI」の生成
	std::unique_ptr<Buff> buff = std::make_unique<Buff>(time, path, position, scale, anchor);
	//初期化
	buff->Initialize();
	return buff;
}

/**
 * @brief 「操作UI」の生成
 *
 * @param[in] respoceKey    対応キー
 * @param[in] position  基準座標
 * @param[in] scale		基準拡大率
 * @param[in] anchor		表示基準
 * @param[in] keyUI		 　 キーUI
 * @param[in] actionUI	　　行動UI
 *
 * @return 操作UIクラス
 */
std::unique_ptr<Key> UIFactory::CreateKeyUI(const std::vector<DirectX::Keyboard::Keys>& respoceKey, const wchar_t* path, 
	const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, 
	const UserInterface::ANCHOR& anchor)
{
	//「操作UI」の生成
	std::unique_ptr<Key> key = std::make_unique<Key>(respoceKey);
	//初期化
	key->Initialize();
	key->Create(path,position,scale,anchor);
	return key;
}

/**
 * @brief 「スコアUI」の生成
 *
 * @param[in] referenceUI   情報
 * @param[in] scoreUI  　   スコア
 *
 * @return スコアUIクラス
 */
std::unique_ptr<Score> UIFactory::CreateScoreUI( const Score::UIInfo& scoreUI,const Score::UIInfo& referenceUI)
{
	//「スコアUI」の生成
	std::unique_ptr<Score> score = std::make_unique<Score>(scoreUI,referenceUI);
	//初期化
	score->Initialize();

	return score;
}
