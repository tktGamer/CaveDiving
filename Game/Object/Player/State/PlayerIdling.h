/**
 * @file   PlayerIdling.h
 *
 * @brief  �v���C���[�̑ҋ@��ԂɊւ���w�b�_�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t 2025/
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once
#ifndef PLAYER_IDLING_DEFINED
#define PLAYER_IDLING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
// �N���X�̐錾 ===============================================================
class Player;

// �N���X�̒�` ===============================================================
/**
  * @brief �ҋ@���
  */
class PlayerIdling : public IState
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �v���C���[
	Player* m_player;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	PlayerIdling(Player* soldier);
	// �f�X�g���N�^
	~PlayerIdling();
	// ����������
	void Initialize();
	// ���O�X�V����
	void PreUpdate();
	// �X�V����
	void Update(const float& elapsedTime);
	// ����X�V����
	void PostUpdate();
	// �`�悷��
	void Render();
	// �㏈�����s��
	void Finalize();

};

#endif		// PLAYER_IDLING_DEFINED
