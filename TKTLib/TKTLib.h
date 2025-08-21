#pragma once
#include<iostream>
#include<ctime>
#include<random>
#include <codecvt>
#include"TKTLib/ModelParams.h"

namespace TKTLib
{

	/**
	 * @brief world�s����擾����
	*
	*  @param[in] pos  ���W
	*  @param[in] rot�@�I�C���[�p
	*  @param[in] sca�@�g�嗦
	*
	* @return world�s��
	*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix
		(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 rot,
		DirectX::SimpleMath::Vector3 sca
		)
	{
		//���s�ړ��s����쐬����
		DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(pos);
		//Y���̉�]�s����쐬����
		DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(rot.y);
		//X���̉�]�s����쐬����
		DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(rot.x);
		//Z���̉�]�s����쐬����
		DirectX::SimpleMath::Matrix rotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(rot.z);
		//�g�嗦�s����쐬����
		DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(sca);
		return scale * rotY * rotX * rotZ * tras;
	}
	/**
	 * @brief world�s����擾����
	*
	*  @param[in] pos  ���W
	*  @param[in] q    �N�H�[�^�j�I��
	*  @param[in] sca�@�g�嗦
	*
	* @return world�s��
	*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix
		(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Quaternion q,
		DirectX::SimpleMath::Vector3 sca
		)
	{
		//���s�ړ��s����쐬����
		DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(pos);
		//Y���̉�]�s����쐬����
		DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(q);
		//�g�嗦�s����쐬����
		DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(sca);
		return scale *rotate * tras;
	}


	/**
	 * @brief ��������
	 *
	 * @param[in] min �ŏ��l
	 * @param[in] max �ő�l
	 *
	 * @return ����
	 */
	inline int GetRand(int min, int max) 
	{
		//�����_��������
		//���������@
		std::random_device random;
		//�^������
		std::mt19937 randomGenerator =std::mt19937(random());
		//��l���z
		std::uniform_int_distribution<> distribution;
		//�����擾
		distribution = std::uniform_int_distribution<>(min, max);
		return distribution(randomGenerator);
	}
	inline double GetRand(double min, double max) 
	{
		//�����_��������
		//���������@
		std::random_device random;
		//�^������
		std::mt19937 randomGenerator =std::mt19937(random());
		//��l���z
		std::uniform_real_distribution<> distribution;
		//�����擾
		distribution = std::uniform_real_distribution<>(min, max);
		return distribution(randomGenerator);
	}


	/**
	 * @brief ���`���
	 *
	 * @param[in] start �J�n�l
	 * @param[in] end   �I���l
	 * @param[in] t     ��ԌW��(0.0�`1.0)
	 *
	 * @return ��Ԍ���
	 */
	template<typename T>
	inline T Lerp(T start, T end, float t) 
	{
		return start + (end - start) * t;
	}


	/**
	 * @brief 
	 *
	 * @param[in] t     �l
	 * @param[in] min   �ŏ��l
	 * @param[in] max   �ő�l
	 *
	 * @return 
	 */
	template<typename T>
	inline T Clamp(T t,T min, T max) 
	{
		return std::min(std::max(t, min), max);
	}



	/**
	 * @brief wchar_t����string�ɕϊ�
	 *
	 * @param[in] wchar_t������
	 *
	 * @return string������
	 */
	inline std::string WcharToString(wchar_t const* wchar_str)
	{
		// wchar_t ���� UTF-8 �ւ̕ϊ�
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(wchar_str);
	}

	/**
	 * @brief string����wchar_t�ɕϊ�
	 *
	 * @param[in] string������
	 *
	 * @return wchar_t������
	 */
	inline wchar_t* StringToWchar(const std::string& str)
	{
		// UTF-8 ���� wchar_t �ɕϊ�
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring wide_str = converter.from_bytes(str);

		// wchar_t* ��Ԃ�
		size_t size_needed = wide_str.size() + 1;  // +1 for null-terminator
		wchar_t* result = new wchar_t[size_needed];

		// wcscpy_s ���g���Ĉ��S�ɃR�s�[
		wcscpy_s(result, size_needed, wide_str.c_str());

		return result;
	}
	/**
	 * @brief string����wstring�ɕϊ�
	 *
	 * @param[in] string������
	 *
	 * @return wstring������
	 */
	inline std::wstring StringToWstring(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}


	//�G���[�̎��
	enum class ErrorType
	{
		None,			///< �G���[�Ȃ�
		FileNotFound,	///< �t�@�C����������Ȃ�����
		UnknownError,	///< �s���ȃG���[
	};

	/**
     * @brief �t�@�C����������Ȃ������Ƃ��̃G���[���b�Z�[�W
	 *
	 * @param[in] filename �G���[�t�@�C����
	 *
	 * @return �@�Ȃ�
	 */
	inline void ShowErrorMessage(const std::string& filename, const std::string& fullPath , ErrorType eType)
	{
		std::wstring errorMessage = L"�u" + StringToWstring(filename) + L"�v";
		std::wstring errorType=L"ERROR";

		switch (eType)
		{
		case TKTLib::ErrorType::None:
			break;
		case TKTLib::ErrorType::FileNotFound:
			errorType = L"�ǂݍ��݃G���[";
			errorMessage += L"�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n";
			errorMessage += StringToWstring(fullPath) + L"�Ƀt�@�C�������邩�m�F���Ă�������";
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