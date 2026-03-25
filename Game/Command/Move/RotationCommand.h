/**
 * @file   RotationCommand.h
 *
 * @brief  回転コマンドに関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/22
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Interface/ICommand.h"
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 回転コマンド
  */
class RotationCommand : public ICommand
{
// クラス定数の宣言 -------------------------------------------------
public:
	//１秒あたりの回転量
	static constexpr  float ROTATION_SPEED_Y_ANGLE = DirectX::XMConvertToRadians(180.0f);

// メンバ関数の宣言 -------------------------------------------------
//　取得・設定
public:
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	RotationCommand(const float& direction);
	// デストラクタ
	~RotationCommand();


// 操作
public:
	//コマンド実行
	void Execute(const int& objectID) override;

//　内部操作
private:
// データメンバの宣言 -----------------------------------------------
private:
	//回転方向
	float m_direction;
};

