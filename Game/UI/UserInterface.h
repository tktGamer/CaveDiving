/**
 * @file   UserInterface.h
 *
 * @brief  ���[�U�[�C���^�[�t�F�C�X�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"
#include"../Shader.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief ���[�U�[�C���^�[�t�F�C�X
  */
class UserInterface
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	//UI�̃A���J�[�|�C���g
	enum ANCHOR
	{
		TOP_LEFT = 0,
		TOP_CENTER,
		TOP_RIGHT,

		MIDDLE_LEFT,
		MIDDLE_CENTER,
		MIDDLE_RIGHT,

		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT

	};

	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector2	windowSize;
		float AlphaData;
		float dammy;
	};

	enum  UIShader
	{
		Menu = 0,
		Gauge,
		Magazine,
		Clock
	};

// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^

	DX::DeviceResources* m_pDR;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	DirectX::CommonStates* m_states;
	// �e�N�X�`���n���h��
	ID3D11ShaderResourceView** m_texture;
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	int m_windowWidth, m_windowHeight;
	int m_textureWidth, m_textureHeight;

	DirectX::SimpleMath::Vector2 m_scale;
	DirectX::SimpleMath::Vector2 m_baseScale;
	DirectX::SimpleMath::Vector2 m_position;

	ANCHOR m_anchor;

	float m_renderRatio;
	float m_renderRatioOffset;


// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	UserInterface();

	// �f�X�g���N�^
	~UserInterface();


// ����
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	void Create( const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		);


	void SetWindowSize(const int& width, const int& height);

	void SetScale(DirectX::SimpleMath::Vector2 scale);
	DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }
	DirectX::SimpleMath::Vector2 GetBaseScale() { return m_baseScale; }
	void SetPosition(DirectX::SimpleMath::Vector2 position);
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }
	void SetAnchor(ANCHOR anchor);
	ANCHOR GetAnchor() { return m_anchor; }

	void SetRenderRatio(float ratio);
	float GetRenderRatio() { return m_renderRatio; }

	void SetRenderRatioOffset(float offset);
	float GetRenderRatioOffset() { return m_renderRatioOffset; }

//�@�擾�E�ݒ�
public:

//�@��������
private:

};

