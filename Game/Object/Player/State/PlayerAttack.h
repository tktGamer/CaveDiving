/**
 * @file   PlayerAttack.h
 *
 * @brief  �v���C���[�̍U����ԂɊւ���w�b�_�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t 2025/
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once
#ifndef PLAYER_ATTACK_DEFINED
#define PLAYER_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
#include"Game/Object/Player/Hand.h"
#include"../State/AttackMotion/AttackMotion.h"
// �N���X�̐錾 ===============================================================
class Player;

// �N���X�̒�` ===============================================================
/**
  * @brief �U�����
  */
class PlayerAttack : public IState
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

	//���[�V�����������
	Hand* m_pHand;
	//
	float m_motionLerp;

	AttackMotion m_attackMotion;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	PlayerAttack(Player* player,Hand* hand);
	// �f�X�g���N�^
	~PlayerAttack();
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


	bool Motion();
	bool Motion2();
	bool Motion3();

};

#endif		// PLAYER_IDLING_DEFINED
