/**
 * @file   GemSelect.cpp
 *
 * @brief  ��ΑI��UI�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include"GemSelect.h"
#include"../CaveDiving/Game/Common/ResourceManager.h"
#include"Game/Message/Messenger.h"
GemSelect::GemSelect()
    : m_menuIndex(0)
    , m_windowHeight(0)
    , m_windowWidth(0)
    , m_baseTexturePath(nullptr)
    ,m_pGemManager{GemManager::GetInstance()}
{
   
}

GemSelect::~GemSelect()
{
}

void GemSelect::Initialize(int width,int height)
{
    m_windowWidth = width;
    m_windowHeight = height;

    //  �w�i�ƂȂ�E�B���h�E�摜��ǂݍ���
    m_baseTexturePath = L"Resources/Textures/window.png";


}

void GemSelect::Update()
{
    auto tracker = Graphics::GetInstance()->GetKeyboardTracker();

    if (tracker->pressed.Right)
    {
        //  ���L�[����������A�I����1�i�߂�
        m_menuIndex += 1;
        //  ���j���[�A�C�e�����̍ő�l�𒴂��Ȃ��悤�ɐ���
        m_menuIndex %= m_userInterface.size();
    }
    if (tracker->pressed.Left)
    {
        //  ���L�[����������A�I����1�߂��B
        //  �������A�I���̃I�[�o�[������Z�̗]��ŕ␳���邽�߁A�i�A�C�e���̍ő�� - 1�j�𑫂��ĕK���]��Ōv�Z����`�ɂ��Ă����B
        //  �ȉ��̎��́A�Ⴆ�΃��j���[��4��������A���ݒl��3�𑫂��Ƃ������B
        //  ��j�I�𒆂̃��j���[��0�`3�܂ł������2�Ԗڂ������ꍇ�A
        //  (2 + (4 - 1)) % 4 = 1 �� �I�𒆂̔ԍ���1������
        //  �Ƃ�������
        m_menuIndex += static_cast<unsigned int>(m_userInterface.size()) - 1;
        m_menuIndex %= m_userInterface.size();
    }

    //�X�y�[�X�L�[����������
    if (tracker->pressed.Space) 
    {
        auto p= Messenger::GetInstance()->GetObject(-1);
        
        m_pGems[m_menuIndex];
        m_pGemManager->RandomSelection();
    }

    //  �e�A�C�e���ɕ\������摜�̏����T�C�Y��ݒ肷��
    for (int i = 0; i < m_userInterface.size(); i++)
    {
        //m_base[i]->SetScale(m_base[i]->GetBaseScale());
        m_userInterface[i]->SetScale(m_userInterface[i]->GetBaseScale());
    }

    //  �I�𒆂̏����T�C�Y���擾����
    DirectX::SimpleMath::Vector2 select = m_userInterface[m_menuIndex]->GetBaseScale();
    //  �I����ԂƂ��邽�߂̕ω��p�T�C�Y���Z�o����
    DirectX::SimpleMath::Vector2 selectScale = DirectX::SimpleMath::Vector2::Lerp(m_userInterface[m_menuIndex]->GetBaseScale(), DirectX::SimpleMath::Vector2::One, 1);
    //  �I����Ԃ͏�����ԁ{30���̑傫���Ƃ���
    select += selectScale * 0.3f;
    //  �Z�o��̃T�C�Y�����݂̃T�C�Y�Ƃ��Đݒ肷��
    m_userInterface[m_menuIndex]->SetScale(select);
    //  �w�i�p�̃E�B���h�E�摜�ɂ����������̒l��ݒ肷��
   // m_base[m_menuIndex]->SetScale(select);
}

void GemSelect::Render()
{
       for (int i = 0; i < m_base.size(); i++)
        {
            //  �A�C�e���p�E�B���h�E�w�i��\��
            m_base[i]->Draw();
        }
       for (int i = 0; i < m_userInterface.size(); i++)
        {
            //  ���ۂɕ\���������A�C�e���摜��\��
            m_userInterface[i]->Draw();
        }
}

void GemSelect::Add(Gem::GemImagePath gemImagePath, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, UserInterface::ANCHOR anchor)
{

    //  �w�i�p�̃E�B���h�E�摜���ǉ�����
    std::unique_ptr<UserInterface> base = std::make_unique<UserInterface>();
    base->Create(
         gemImagePath.panel
        , position
		, { 1.0f, 1.0f }
        , anchor
        );

    base->SetWindowSize(m_windowWidth, m_windowHeight);

    //  �w�i�p�̃A�C�e�����V�����ǉ�����
    m_userInterface.push_back(std::move(base));

}

void GemSelect::Randomize()
{
    m_userInterface.clear();
    m_base.clear();
    for (int i = 0; i < 3; i++)
    {
        m_pGems[i] = m_pGemManager->RandomSelection();
        Gem::GemAbility ability = m_pGems[i]->GetAbility();
        Gem::GemImagePath imagePath = m_pGems[i]->GetImagePath();
        Add(imagePath, { PANNEL_X+PANNEL_X*i,310.0f }, { 0.35f,0.35f }, UserInterface::ANCHOR::MIDDLE_CENTER);
    }
}


