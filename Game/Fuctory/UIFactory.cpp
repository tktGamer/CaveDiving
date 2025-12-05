/**
 * @file   UIFactory.cpp
 *
 * @brief  UI生成に関するソースファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2025/11/25
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
std::unique_ptr<UserInterface> UIFactory::CreateUserInterface(const wchar_t* path, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, const UserInterface::ANCHOR& anchor)
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
 *
 * @return 宝石選択UIクラス
 */
std::unique_ptr<GemSelect> UIFactory::CreateGemSelect(GemSelectUIManager* pGemSelectUIManager)
{
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//「宝石選択UI」の生成
	std::unique_ptr<GemSelect> gemSelect = std::make_unique<GemSelect>(w,h,pGemSelectUIManager );
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
 *
 * @return 宝石入れ替えUIクラス
 */
std::unique_ptr<ChangeGem> UIFactory::CreateChangeGem(GemSelectUIManager* pGemSelectUIManager)
{
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//入れ替え先の宝石の取得
	Gem* pGem = GemManager::GetInstance()->GetReplacementGem();

	//「宝石入れ替えUI」の生成
	std::unique_ptr<ChangeGem> changeGem = std::make_unique<ChangeGem>(w, h, pGem, pGemSelectUIManager);
	changeGem->Initialize();

	return std::move(changeGem);
}


/**
 * @brief 「所持している宝石を表示するUI」の生成
 *
 * @param[in] なし
 *
 * @return 所持している宝石を表示するUIクラス
 */
std::unique_ptr<HoldGem> UIFactory::CreateHoldGem()
{
	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);


	//「所持している宝石を表示するUI」の生成
	std::unique_ptr<HoldGem> holdGem = std::make_unique<HoldGem>(w, h);
	holdGem->Initialize();

	return std::move(holdGem);
}


/**
 * @brief 「所持している宝石の内1つの情報を表示するUI」の生成
 *
 * @param[in] なし
 *
 * @return 所持している宝石の内1つの情報を表示するUIクラス
 */
std::unique_ptr<HoldGemInfoDraw> UIFactory::CreateHoldGemInfoDraw()
{

	//スクリーンサイズ取得
	int w, h;
	Graphics::GetInstance()->GetScreenSize(w, h);

	//「所持している宝石の内1つの情報を表示するUI」の生成
	std::unique_ptr<HoldGemInfoDraw> holdGemInfo = std::make_unique<HoldGemInfoDraw>(w, h);
	holdGemInfo->Initialize();

	return std::move(holdGemInfo);
}
