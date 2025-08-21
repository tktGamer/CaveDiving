#pragma once
#ifndef BAT_IDLING_DEFINED
#define BAT_IDLING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"
class Bat;

// BatIdling�N���X���`����
class BatIdling : public IState
{
public:
	// �R���X�g���N�^
	BatIdling(Bat* bat);
	// �f�X�g���N�^
	~BatIdling();
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
	Bat* m_bat;
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
};

#endif		// SOLDIER_IDLING_DEFINED
