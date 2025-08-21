#pragma once
#ifndef BAT_MOVING_DEFINED
#define BAT_MOVING_DEFINED
#include "Game/Interface/IState.h"
#include "Game/Common/Graphics.h"

class Bat;
// BatMoving�N���X���`����
class BatMoving : public IState
{
public:
	// �R���X�g���N�^
	BatMoving(Bat* bat);
	// �f�X�g���N�^
	~BatMoving();
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
#endif		// BAT_IDLING_DEFINED
