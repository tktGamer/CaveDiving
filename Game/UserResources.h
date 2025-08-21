//--------------------------------------------------------------------------------------
// File: UserResources.h
//
// �V�[���֓n�����[�U�[���\�[�X�N���X�i�T���v���j
//
// Date: 2025.2.28
//--------------------------------------------------------------------------------------
#pragma once

#include "StepTimer.h"
#include "DeviceResources.h"
#include "../Game/Common/DebugFont.h"

// �e�V�[���ɓn�����ʃ��\�[�X���L�q���Ă�������
class UserResources
{
private:

	// �X�e�b�v�^�C�}�[
	DX::StepTimer* m_timer;


	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardTracker;

	// �}�E�X�X�e�[�g�g���b�J�[
	DirectX::Mouse::ButtonStateTracker* m_mouseTracker;

	// �f�o�b�O�p������\���ւ̃|�C���^
	Ito::DebugFont* m_debugFont;

	// ���ʃX�e�[�g
	DirectX::CommonStates* m_states;

public:

	// �R���X�g���N�^
	UserResources()
		: m_timer(nullptr)
		, m_keyboardTracker(nullptr)
		, m_mouseTracker(nullptr)
		, m_debugFont(nullptr)
		, m_states(nullptr)
	{
	}

	// ------------------------------------------ //
	// �X�e�b�v�^�C�}�[	
	// ------------------------------------------ //

	// �X�e�b�v�^�C�}�[��ݒ肷��֐�
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }

	// �X�e�b�v�^�C�}�[���擾����֐�
	DX::StepTimer* GetStepTimer() { return m_timer; }


	// ------------------------------------------ //
	// �L�[�{�[�h�X�e�[�g�g���b�J�[	
	// ------------------------------------------ //

	// �L�[�{�[�h�X�e�[�g�g���b�J�[��ݒ肷��֐�
	void SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* tracker) { m_keyboardTracker = tracker; }

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����֐�
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() { return m_keyboardTracker; }

	// ------------------------------------------ //
	// �}�E�X�X�e�[�g�g���b�J�[	
	// ------------------------------------------ //

	// �}�E�X�X�e�[�g�g���b�J�[��ݒ肷��֐�
	void SetMouseStateTracker(DirectX::Mouse::ButtonStateTracker* tracker) { m_mouseTracker = tracker; }

	// �}�E�X�X�e�[�g�g���b�J�[���擾����֐�
	DirectX::Mouse::ButtonStateTracker* GetMouseStateTracker() { return m_mouseTracker; }

	// ------------------------------------------ //
	// ���ʃX�e�[�g	
	// ------------------------------------------ //

	// ���ʃX�e�[�g��ݒ肷��֐�
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }

	// ���ʃX�e�[�g���擾����֐�
	DirectX::CommonStates* GetCommonStates() { return m_states; }

	// ------------------------------------------ //
	// �f�o�b�O�t�H���g	
	// ------------------------------------------ //

	// �f�o�b�O�t�H���g��ݒ肷��֐�
	void SetDebugFont(Ito::DebugFont* debugFont) { m_debugFont = debugFont; }

	// �f�o�b�O�t�H���g���擾����֐�
	Ito::DebugFont* GetDebugFont() { return m_debugFont; }

};

