/**
 * @file   InputHandler.h
 *
 * @brief  入力管理に関するヘッダファイル
 *
 * @author 制作者名　福地貴翔
 *
 * @date   日付　2026/03/22
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include"Game/Interface/ICommand.h"
#include <Keyboard.h>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief 入力管理
  */
class InputHandler
{
// クラス定数の宣言 -------------------------------------------------
public:
	//入力状態
	enum class InputType
	{
		// 押した瞬間
		Pressed,  
		// 離した瞬間
		Released,   
		// 押し続けてる
		Hold        
	};
	//入力キーと対応コマンド
	struct InputCommand
	{
		DirectX::Keyboard::Keys key;
		InputType type;
		std::unique_ptr<ICommand> command;
	};
// メンバ関数の宣言 -------------------------------------------------
	//　取得・設定
public:
	
// コンストラクタ/デストラクタ
	// コンストラクタ
	InputHandler();
	// デストラクタ
	~InputHandler();
// 操作
	//コマンド登録
	void Register(const DirectX::Keyboard::Keys& key, const InputType& type, std::unique_ptr<ICommand> cmd);
	//キー判定
	void Update(const int& objectID);
//　内部操作
private:

// データメンバの宣言 -----------------------------------------------
private:
	//キーと対応コマンド配列
	std::vector<InputCommand> m_commands;
};