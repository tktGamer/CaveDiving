/**
 * @file   UIFactory.h
 *
 * @brief  UIの生成に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef UI_FACTORY_DEFINED
#define UI_FACTORY_DEFINED
// ヘッダファイルの読み込み ===================================================
#include"../UI/GemSelectUIManager.h"
#include"../UI/Menu/Menu.h"
#include"../UI/Gauge/Gauge.h"
#include"../UI/HoldGem/HoldGem.h"
#include"../UI/HoldGem/HoldGemInfoDraw.h"
#include"../UI/GemSelect/GemSelect.h"
#include"../UI/GemSelect/ChangeConfirm.h"
#include"../UI/GemSelect/ChangeGem.h"
// ファクトリクラスを定義する
class UIFactory 
{
public:


	// 「UI」を生成する
	static std::unique_ptr<UserInterface> CreateUserInterface(
		  const wchar_t* path
		, const DirectX::SimpleMath::Vector2& position
		, const DirectX::SimpleMath::Vector2& scale
		, const UserInterface::ANCHOR& anchor
		);

	// 「メニュー」を生成する
	static std::unique_ptr<Menu> CreateMenu(
	);

	// 「ゲージ」を生成する
	static std::unique_ptr<Gauge> CreateGauge(
	);

	// 「宝石選択UI」を生成する
	static std::unique_ptr<GemSelect> CreateGemSelect(
		  GemSelectUIManager* pGemSelectUIManager
		);

	// 「入れ替え確認UI」を生成する
	static std::unique_ptr<ChangeConfirm> CreateChangeConfirm(
		  GemSelectUIManager* pGemSelectUIManager
		);

	// 「宝石入れ替えUI」を生成する
	static std::unique_ptr<ChangeGem> CreateChangeGem(
		  GemSelectUIManager* pGemSelectUIManager
		);

	// 「所持している宝石を表示するUI」を生成する
	static std::unique_ptr<HoldGem> CreateHoldGem(
		);

	// 「所持している宝石の内1つの情報を表示するUI」を生成する
	static std::unique_ptr<HoldGemInfoDraw> CreateHoldGemInfoDraw(
		);


};

#endif		// UI_FACTORY_DEFINED