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

// クラスの定義 ===============================================================
/**
 * @brief グラフィック
 */
class BinaryFile
{
protected:

	//	データ
	std::shared_ptr<char[]> m_data;

	//	サイズ
	unsigned int m_size;

public:

	//	ファイル名を指定してロード
	std::unique_ptr<BinaryFile> LoadFile( wchar_t const* fileName);

	BinaryFile();

	//	ムーブコンストラクタ
	BinaryFile(BinaryFile* in);

	//	アクセサ
	char* GetData() { return m_data.get(); }
	unsigned int GetSize() { return m_size; }
};