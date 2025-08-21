/**
 * @file   Gauge.h
 *
 * @brief  �Q�[�WUI�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "../UserInterface.h"
#include"Game/Object/Gem/GemManager.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief ���[�U�[�C���^�[�t�F�C�X
  */

class Gauge
{
public:


private:


	std::unique_ptr<UserInterface> m_gauge;
	std::unique_ptr<UserInterface> m_frame;


	const wchar_t* m_baseTexturePath;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	//�Q�[�W�̎Q�Ƃ���l
	const int* m_currentValue;
	const int* m_maxValue;
public:
	Gauge();
	~Gauge();

	void Initialize(int width, int height);
	void Update();
	void Render();

	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);

	void SetValue(const int& current, const int& max);

};
