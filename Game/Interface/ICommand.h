/**
 * @file   ICommand.h
 *
 * @brief  入力処理のインターフェイスに関するヘッダファイル
 *
 * @author 制作者名  福地貴翔
 *
 * @date   日付　2026/03/22
 */
 // 多重インクルードの防止 =====================================================
#pragma once
#ifndef ICOMMAND_DEFINED
#define ICOMMAND_DEFINED
// ヘッダファイルの読み込み ===================================================

// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
  * @brief ICommandインターフェースを定義する
  */
class ICommand
{
public:
	//デストラクタ
	virtual ~ICommand() = default;
// 操作
public:
	// コマンドを送信
	virtual void Execute(const int& objectID) = 0;
};

#endif	// ICOMMAND_DEFINED
