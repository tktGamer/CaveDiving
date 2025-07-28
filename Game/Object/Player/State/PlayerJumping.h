#pragma once
#ifndef PLAYER_JUMPING_DEFINED
#define PLAYER_JUMPING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

class Player;
// PlayerJumping�N���X���`����
class PlayerJumping : public IState
{
public:
	// �R���X�g���N�^
	PlayerJumping(Player* soldier);
	// �f�X�g���N�^
	~PlayerJumping();
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

private:
	// �v���C���[
	Player* m_player;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
};
#endif		// SOLDIER_IDLING_DEFINED
