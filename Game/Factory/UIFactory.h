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
#include"../UI/Number/NumberControl.h"
#include"../UI/Number/CountUpNumber.h"
#include"../UI/Animation2D.h"
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
		 DirectX::SoundEffect* cursolSound
	);

	// 「ゲージ」を生成する
	static std::unique_ptr<Gauge> CreateGauge(
	);

	// 「宝石選択UI」を生成する
	static std::unique_ptr<GemSelect> CreateGemSelect(
		  GemSelectUIManager* pGemSelectUIManager,
		const std::vector<int>& gemID
		);

	// 「入れ替え確認UI」を生成する
	static std::unique_ptr<ChangeConfirm> CreateChangeConfirm(
		  GemSelectUIManager* pGemSelectUIManager
		);

	// 「宝石入れ替えUI」を生成する
	static std::unique_ptr<ChangeGem> CreateChangeGem(
		  GemSelectUIManager* pGemSelectUIManager,
		const std::vector<int>& gemID
		);

	// 「所持している宝石を表示するUI」を生成する
	static std::unique_ptr<HoldGem> CreateHoldGem(
		const std::vector<int>& gemID
		);

	// 「所持している宝石の内1つの情報を表示するUI」を生成する
	static std::unique_ptr<HoldGemInfoDraw> CreateHoldGemInfoDraw(
		const std::vector<int>& gemID
		);

	// 「数字UI」を生成する
	static std::unique_ptr<NumberControl> CreateNumberUI(
			const NumberControl::NumberTextureData& data
		,   const DirectX::SimpleMath::Vector2& pos
		,   const DirectX::SimpleMath::Vector2& scale
		,   const DirectX::SimpleMath::Vector4& color
		,   const int& initNumber = 0 
		,   const int& minDigit   = 1
		);

	// 「数字が増加する機能をもつUI」を生成する
	static std::unique_ptr<CountUpNumber> CreateCountUpNumberUI(
			std::unique_ptr<NumberControl> numberUI
		,	std::unique_ptr<UserInterface> numberInfoUI
		,   const int& initNumber
		,   const int& targetNumber   
		,   const int& stepNumber
		);

	// 「2DアニメーションUI」を生成する
	static std::unique_ptr<Animation2D> CreateAnimation2DUI(
		const wchar_t* texturepath,
		const Animation2D::AnimationTexture& textureInfo,
		const float& animationTime,
		const bool& isLoop,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale = DirectX::SimpleMath::Vector2::One
	);
};

#endif		// UI_FACTORY_DEFINED