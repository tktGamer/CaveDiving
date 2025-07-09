#pragma once
#ifndef PLAYER_MOVING_DEFINED
#define PLAYER_MOVING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

class Player;
// PlayerMoving�N���X���`����
class PlayerMoving : public IState
{
public:
	// �R���X�g���N�^
	PlayerMoving(Player* soldier);
	// �f�X�g���N�^
	~PlayerMoving();
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
	// �\���W���[
	Player* m_player;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �v���C���[���f��
	DirectX::Model* m_playerModel;
};

#endif		// SOLDIER_IDLING_DEFINED
