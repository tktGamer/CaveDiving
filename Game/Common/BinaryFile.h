/**
 * @file   BinaryFile.h
 *
 * @brief  バイナリ形式ファイル読み込みに関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */
 // 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include<unordered_map>
// クラスの宣言 ===============================================================

// クラスの定義 ===============================================================
/**
 * @brief バイナリ形式ファイル読み込み
 */
class BinaryFile
{
// クラス定数の宣言 -------------------------------------------------
public:

// データメンバの宣言 -----------------------------------------------
private:

	//	データ
	std::shared_ptr<char[]> m_data;

	//	サイズ
	unsigned int m_size;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	//コンストラクタ
	BinaryFile();

	//	ムーブコンストラクタ
	BinaryFile(BinaryFile* in);
	//デストラクタ
	~BinaryFile();

// 操作
public:
	//	ファイル名を指定してロード
	std::unique_ptr<BinaryFile> LoadFile( wchar_t const* fileName);

//　取得・設定
public:
	//	アクセサ
	char* GetData() { return m_data.get(); }
	unsigned int GetSize() { return m_size; }
};