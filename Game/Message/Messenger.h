#pragma once
#ifndef MESSENGER_DEFINED
#define MESSENGER_DEFINED
#include "Game/Message/Message.h"
#include <unordered_map>

class GameObject;

// Messenger�N���X
class Messenger
{
public:
	// �I�u�W�F�N�g���擾����
	GameObject* GetObject(int objectID);
	// �o�ߎ��Ԃ��擾����
	float GetElapsedTime() const { return m_elapsedTime; }
	// �o�ߎ��Ԃ�ݒ肷��
	void SetElapsedTime(const float& elapsedTime) { m_elapsedTime = elapsedTime; }

public:
	// Messenger�N���X�̃C���X�^���X���擾����
	static Messenger* GetInstance();
	// Messenger�N���X�̃C���X�^���X��j������
	static void DestroyInstance();
	// �I�u�W�F�N�g��o�^����
	void Register(int objectID, GameObject* object);
	// �I�u�W�F�N�g�̓o�^����������
	void UnRegister(int objectID);
	// ���b�Z�[�W�𑗐M����
	void Notify(int objectID, Message::MessageID);

private:
	// �R�s�[�E���[�u�֎~
	Messenger(const Messenger&) = delete;
	Messenger& operator=(const Messenger&) = delete;
	Messenger(Messenger&&) = delete;
	Messenger& operator=(Messenger&&) = delete;
	// �R���X�g���N�^
	Messenger();

private:
	// ���b�Z���W���[�C���X�^���X
	static std::unique_ptr<Messenger> s_messenger;
	// �I�u�W�F�N�gID�ƃI�u�W�F�N�g�}�b�s���O
	std::unordered_map<int, GameObject*> m_objects;
	// �o�ߎ���
	float m_elapsedTime;

};

#endif		// MESSENGER_DEFINED

