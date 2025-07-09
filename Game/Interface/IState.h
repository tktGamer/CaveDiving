#pragma once
#ifndef STATE_DEFINED
#define STATE_DEFINED
#include "StepTimer.h"
#include <Keyboard.h>
#include"Game/Interface/IObserver.h"
#include"Game/Common/Graphics.h"
// IState�C���^�[�t�F�C�X���`���� 
class IState
{
public:
	// ���������� 
	virtual void Initialize() = 0;
	// ���O�X�V����
	virtual void PreUpdate() = 0;
	// ���������s����
	virtual void Update(const float& elapsedTime) = 0;
	// ����X�V����
	virtual void PostUpdate() = 0;
	// �e�N�X�`����`�悷��
	virtual void Render() = 0;
	// ��n��������
	virtual void Finalize() = 0;
	// ���z�f�X�g���N�^
	virtual ~IState() = default;
};

#endif // STATE_DEFINED
