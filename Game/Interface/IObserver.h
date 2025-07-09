#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED
#include "Game/Message/Message.h"

// IObserver�C���^�[�t�F�[�X���`����
class IObserver
{
public:
	// ���b�Z�[�W���󂯎��
	virtual void OnMessegeAccepted(Message::MessageID messageID) = 0;
};

#endif	// IOBSERVER_DEFINED
