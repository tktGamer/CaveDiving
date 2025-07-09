//	b0�ɂ̓}�g���b�N�X3�ƃf�B�t���[�Y�����\���̂Ƃ��ē���邱�Ƃɂ���
cbuffer ConstBuffer : register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
    float4 light;
};

struct VS_IN
{
    float3 Pos : POSITION; //���_���W
    float3 Nor : NORMAL; //���_�@��
    float2 Tex : TEXCOORD;
};

struct VS_OUT
{
    float4 Pos : SV_Position; //���_���W
    float4 Nor : NORMAL0; //���_�@��
    float2 Tex : TEXCOORD;
   
};

struct PS_IN
{
    float4 Pos : SV_POSITION;//�v�Z�ςݍ��W
    float4 Posw : POSITION0; //���[���h���W
    float4 Norw : NORMAL0; //���[���h���W�̖@��
    float2 Tex : TEXCOORD;
    
};