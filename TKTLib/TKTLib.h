#pragma once
#include<iostream>
#include<ctime>
#include<random>
#include <codecvt>
#include"TKTLib/ModelParams.h"

namespace TKTLib
{

	/**
	 * @brief world行列を取得する
	*
	*  @param[in] pos  座標
	*  @param[in] rot　オイラー角
	*  @param[in] sca　拡大率
	*
	* @return world行列
	*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix
		(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 rot,
		DirectX::SimpleMath::Vector3 sca
		)
	{
		//平行移動行列を作成する
		DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(pos);
		//Y軸の回転行列を作成する
		DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(rot.y);
		//X軸の回転行列を作成する
		DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(rot.x);
		//Z軸の回転行列を作成する
		DirectX::SimpleMath::Matrix rotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(rot.z);
		//拡大率行列を作成する
		DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(sca);
		return scale * rotY * rotX * rotZ * tras;
	}
	/**
	 * @brief world行列を取得する
	*
	*  @param[in] pos  座標
	*  @param[in] q    クォータニオン
	*  @param[in] sca　拡大率
	*
	* @return world行列
	*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix
		(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Quaternion q,
		DirectX::SimpleMath::Vector3 sca
		)
	{
		//平行移動行列を作成する
		DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(pos);
		//Y軸の回転行列を作成する
		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(q);
		//拡大率行列を作成する
		DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(sca);
		return scale *rotate * tras;
	}


	/**
	 * @brief 乱数生成
	 *
	 * @param[in] min 最小値
	 * @param[in] max 最大値
	 *
	 * @return 乱数
	 */
	inline int GetRand(int min, int max) 
	{
		//ランダム数生成
		//乱数生成機
		std::random_device random;
		//疑似乱数
		std::mt19937 randomGenerator =std::mt19937(random());
		//一様分布
		std::uniform_int_distribution<> distribution;
		//乱数取得
		distribution = std::uniform_int_distribution<>(min, max);
		return distribution(randomGenerator);
	}
	inline double GetRand(double min, double max) 
	{
		//ランダム数生成
		//乱数生成機
		std::random_device random;
		//疑似乱数
		std::mt19937 randomGenerator =std::mt19937(random());
		//一様分布
		std::uniform_real_distribution<> distribution;
		//乱数取得
		distribution = std::uniform_real_distribution<>(min, max);
		return distribution(randomGenerator);
	}


	/**
	 * @brief 線形補間
	 *
	 * @param[in] start 開始値
	 * @param[in] end   終了値
	 * @param[in] t     補間係数(0.0～1.0)
	 *
	 * @return 補間結果
	 */
	template<typename T>
	inline T Lerp(T start, T end, float t) 
	{
		return start + (end - start) * t;
	}


	/**
	 * @brief 
	 *
	 * @param[in] t     値
	 * @param[in] min   最小値
	 * @param[in] max   最大値
	 *
	 * @return 
	 */
	template<typename T>
	inline T Clamp(T t,T min, T max) 
	{
		return std::min(std::max(t, min), max);
	}



	/**
	 * @brief wchar_tからstringに変換
	 *
	 * @param[in] wchar_t文字列
	 *
	 * @return string文字列
	 */
	inline std::string WcharToString(wchar_t const* wchar_str)
	{
		// wchar_t から UTF-8 への変換
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(wchar_str);
	}

	/**
	 * @brief stringからwchar_tに変換
	 *
	 * @param[in] string文字列
	 *
	 * @return wchar_t文字列
	 */
	inline wchar_t* StringToWchar(const std::string& str)
	{
		// UTF-8 から wchar_t に変換
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring wide_str = converter.from_bytes(str);

		// wchar_t* を返す
		size_t size_needed = wide_str.size() + 1;  // +1 for null-terminator
		wchar_t* result = new wchar_t[size_needed];

		// wcscpy_s を使って安全にコピー
		wcscpy_s(result, size_needed, wide_str.c_str());

		return result;
	}
	/**
	 * @brief stringからwstringに変換
	 *
	 * @param[in] string文字列
	 *
	 * @return wstring文字列
	 */
	inline std::wstring StringToWstring(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}


	//エラーの種類
	enum class ErrorType
	{
		None,			///< エラーなし
		FileNotFound,	///< ファイルが見つからなかった
		UnknownError,	///< 不明なエラー
	};

	/**
     * @brief ファイルが見つからなかったときのエラーメッセージ
	 *
	 * @param[in] filename エラーファイル名
	 *
	 * @return 　なし
	 */
	inline void ShowErrorMessage(const std::string& filename, const std::string& fullPath , ErrorType eType)
	{
		std::wstring errorMessage = L"「" + StringToWstring(filename) + L"」";
		std::wstring errorType=L"ERROR";

		switch (eType)
		{
		case TKTLib::ErrorType::None:
			break;
		case TKTLib::ErrorType::FileNotFound:
			errorType = L"読み込みエラー";
			errorMessage += L"ファイルの読み込みに失敗しました。\n";
			errorMessage += StringToWstring(fullPath) + L"にファイルがあるか確認してください";
			break;
		case TKTLib::ErrorType::UnknownError:
			break;
		default:
			break;
		}

		MessageBox(NULL, errorMessage.c_str(),errorType.c_str(), MB_ICONEXCLAMATION);
		PostQuitMessage(0);
	}

}