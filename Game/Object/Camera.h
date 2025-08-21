#pragma once
// �w�b�_�t�@�C���̓ǂݍ��� ===================================================

class Camera
{

	//�J�����̃^�C�v
	enum class Type
	{
		Type_A,	//�v���C���[��ǔ�����J����
		Type_B	//�v���C���[�̎�����܂��J����
	};

private:

	//���݂̃J�����^�C�v
	Type m_type;



	//��x�N�g��
	DirectX::SimpleMath::Vector3 m_up;
	//�J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_eyePos;
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//�^�[�Q�b�g�̈ʒu
	const DirectX::SimpleMath::Vector3* m_targetPos;
	//�^�[�Q�b�g�̉�]
	const DirectX::SimpleMath::Quaternion* m_targetRotate;
	//�^�[�Q�b�g����̋���
	DirectX::SimpleMath::Vector3 m_distance;
public:
	Camera();

	~Camera();

	void Initialize(DirectX::SimpleMath::Vector3 position);

	void Update(float elapsedTime);


	void Finalize();


	void SetEyePos(DirectX::SimpleMath::Vector3 position);
	void SetEyePosX(float posX);
	void SetEyePosY(float posY);
	void SetEyePosZ(float posZ);
	void SetTartet(const DirectX::SimpleMath::Vector3& targetPos,const DirectX::SimpleMath::Quaternion& rotate);
	void SetDistance(DirectX::SimpleMath::Vector3 distance);
	DirectX::SimpleMath::Vector3 GetEyePos() { return m_eyePos; }
	DirectX::SimpleMath::Matrix GetView();

	DirectX::SimpleMath::Vector3 GetTargetPos() const { return *m_targetPos; }
};

