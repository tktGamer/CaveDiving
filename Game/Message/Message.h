#pragma once
#ifndef MESSAGE_DEFINED
#define MESSAGE_DEFINED

// Message�N���X
// �EIDLING��OFFENSIVE_IDLING�ɕύX����
class Message
{
public:
	// ���b�Z�[�WID
	enum MessageID : int  
	{ 

		// �v���C���[
		IDLING,											// �u�A�C�h�����O�v���
		MOVING,							// �u�ړ��v���
		ATTACK,											// �u�U���v���
		AVOIDANCE,										// �u����v���
		DAMAGED,										// �u�_���[�W�v���
		JUMPING,
	};
};

#endif		// MESSAGE_DEFINED

