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
		// 
		COLLISIONVALID,					// �u�Փ˗L���v���
		COLLISIONINVALID,					// �u�Փ˖����v���
		// ���
		IDLING,							// �u�A�C�h�����O�v���
		MOVING,							// �u�ړ��v���
		ATTACK,							// �u�U���v���
		AVOIDANCE,						// �u����v���
		DAMAGED,						// �u�_���[�W�v���
		JUMPING,
	};
};

#endif		// MESSAGE_DEFINED

