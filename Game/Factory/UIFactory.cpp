/**
 * @file   UIFactory.cpp
 *
 * @brief  UI生成に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/01/12
 */

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "UIFactory.h"

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
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);
	
	
	//「UI」の生成
	std::unique_ptr<UserInterface> ui = std::make_unique<UserInterface>();
	ui->SetWindowSize(w, h);
	ui->Create(path, position, scale, anchor);
	ui->Initialize();

	return std::move(ui);
}

/**
 * @brief 「メニューUI」の生成
 *
 * @param[in] cursolSound カーソル移動時の効果音
 *
 * @return メニューUIクラス
 */
std::unique_ptr<Menu> UIFactory::CreateMenu(DirectX::SoundEffect* cursolSound)
{
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//「メニューUI」の生成
	std::unique_ptr<Menu> menu = std::make_unique<Menu>(w, h,cursolSound);
	menu->Initialize();

	return std::move(menu);

}

/**
 * @brief 「ゲージUI」の生成
 *
 * @param[in] なし
 *
 * @return ゲージUIクラス
 */
std::unique_ptr<Gauge> UIFactory::CreateGauge()
{
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	std::unique_ptr<Gauge> gauge = std::make_unique<Gauge>();
	gauge->Initialize(w, h);

	return std::move(gauge);
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
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//「宝石選択UI」の生成
	std::unique_ptr<GemSelect> gemSelect = std::make_unique<GemSelect>(w,h,gemID,pGemSelectUIManager );
	gemSelect->Initialize();
	return std::move(gemSelect);
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
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//「入れ替え確認UI」の生成
	std::unique_ptr<ChangeConfirm> changeConfirm = std::make_unique<ChangeConfirm>(w, h, pGemSelectUIManager);
	changeConfirm->Initialize();

	return std::move(changeConfirm);
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
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//入れ替え先の宝石の取得
	//Gem* pGem = GemManager::GetInstance()->GetReplacementGem();

	//「宝石入れ替えUI」の生成
	std::unique_ptr<ChangeGem> changeGem = std::make_unique<ChangeGem>(w, h,gemID, pGemSelectUIManager);
	changeGem->Initialize();

	return std::move(changeGem);
}


/**
 * @brief 「所持している宝石を表示するUI」の生成
 *
 * @param[in] gemID  宝石ID
 *
 * @return 所持している宝石を表示するUIクラス
 */
std::unique_ptr<HoldGem> UIFactory::CreateHoldGem(const std::vector<int>& gemID)
{
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);


	//「所持している宝石を表示するUI」の生成
	std::unique_ptr<HoldGem> holdGem = std::make_unique<HoldGem>(w, h,gemID);
	holdGem->Initialize();
	holdGem->ChangeDrawGem(gemID);
	return std::move(holdGem);
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

	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//「所持している宝石の内1つの情報を表示するUI」の生成
	std::unique_ptr<HoldGemInfoDraw> holdGemInfo = std::make_unique<HoldGemInfoDraw>(w, h,gemID);
	holdGemInfo->Initialize();

	return std::move(holdGemInfo);
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
	return std::move(numberControl);
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
	return std::move(numberControl);
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
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);
	animation2D->SetWindowSize(DirectX::SimpleMath::Vector2{ static_cast<float>(w),static_cast<float>(h) });
	return std::move(animation2D);
}

