/**
 * @file   GemSelect.h
 *
 * @brief  ��ΑI��UI�Ɋւ���w�b�_�t�@�C��
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
class GemSelect
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	static constexpr float PANNEL_X = 310.0f;
// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	GemManager* m_pGemManager;

	unsigned int m_menuIndex;

	std::vector<std::unique_ptr<UserInterface>> m_userInterface;
	std::vector<std::unique_ptr<UserInterface>> m_base;

	const wchar_t* m_baseTexturePath;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	DirectX::Keyboard::KeyboardStateTracker m_tracker;

	Gem* m_pGems[3];
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	GemSelect();
	~GemSelect();
	// ����
public:
	void Initialize(int width, int height);
	void Update();
	void Render();

	void Add(Gem::GemImagePath gemImagePath
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, UserInterface::ANCHOR anchor);

	//��΂������_���ɑI��
	void Randomize();
//�@�擾�E�ݒ�
public:

	int GetGemSelectIndex() const { return m_menuIndex; }

//�@��������
private:

};
