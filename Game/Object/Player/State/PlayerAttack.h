#pragma once
#ifndef PLAYER_ATTACK_DEFINED
#define PLAYER_ATTACK_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
#include"Game/Object/Player/Hand.h"

class Player;
// PlayerAttack�N���X���`����
class PlayerAttack : public IState
{
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
};

#endif		// SOLDIER_IDLING_DEFINED
