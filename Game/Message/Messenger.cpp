#include "pch.h"
#include "Game/Message/Messenger.h"
#include "Game/Object/GameObject.h"

// s_messenger������������
std::unique_ptr<Messenger> Messenger::s_messenger = nullptr;

// �R���X�g���N�^
Messenger::Messenger()
{
}

// Messenger�N���X�̃C���X�^���X���擾����
Messenger* Messenger::GetInstance()
{
	// Messenger�N���X�̃C���X�^���X��������Ă��Ȃ��ꍇ
	if (s_messenger == nullptr)
	{
		// Messenger�N���X�̃C���X�^���X�𐶐�����
		s_messenger = std::unique_ptr<Messenger>(new Messenger());
	}
	// Messenger�N���X�̃C���X�^���X��Ԃ�
	return s_messenger.get();
}

// �C���X�^���X��j������
void Messenger::DestroyInstance()
{ 
	// Messenger�N���X�̃C���X�^���X�����Z�b�g����
	s_messenger.reset();
}

// �I�u�W�F�N�g��o�^����
void Messenger::Register(int objectID, GameObject* object)
{
	// �I�u�W�F�N�gID�ƃI�u�W�F�N�g��o�^����
	m_objects.emplace(objectID, object);
}

// �I�u�W�F�N�g�̓o�^����������
void Messenger::UnRegister(int objectID)
{
	// �I�u�W�F�N�gID�����݂���ꍇ�ɂ̂ݍ폜����
	m_objects.erase(objectID);
}

// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
void Messenger::Notify(int objectID, Message::MessageID messageID)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (it != m_objects.end())
	{
		// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
		it->second->OnMessegeAccepted(messageID);
	}
}

// �I�u�W�F�N�g���擾����
GameObject* Messenger::GetObject(int objectID)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (it != m_objects.end())
	{
		// �I�u�W�F�N�g���擾����
		return it->second;
	}
	return nullptr;
}