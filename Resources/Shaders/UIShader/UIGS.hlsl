#include "UI.hlsli"

static const unsigned int vnum = 4;

//	w��0���ƍs��v�Z�����������Ȃ�̂�1�ɕύX
static const float4 offset_array[vnum] =
{
	float4( 0.0f,  1.0f, 0.0f, 0.0f),	//	����
	float4( 1.0f,  1.0f, 0.0f, 0.0f),	//	�E��
	float4( 0.0f,  0.0f, 0.0f, 0.0f),	//	����
	float4( 1.0f,  0.0f, 0.0f, 0.0f),	//	�E��

};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output
)
{
	for (uint i = 0; i < vnum; i++)
	{
		//	�W�I���g���o��
		PS_INPUT element;
		
		//	���_�ɓ���Ă������X���󂯎��
		float2 window = windowSize;
		float4 rect = input[0].color;
		//	rect(input[0].color)��xy�ɂ́A�A���J�[���W�������Ă���(UserInterface.cpp��Render�֐��`�����)
		float2 pos = (rect.xy / window.xy) * 2.0f;
		//	rect(input[0].color)��zw�ɂ́A�摜�T�C�Y�������Ă���(������UserInterface.cpp��Render�֐��`�����)
		float2 size = (rect.zw / window.xy);

		float2 scale = input[0].pos.xy;
		//	�A���J�[�^�C�v���Ƃɕ␳������W�����肷��
		uint anc = input[0].pos.z;
		float2 anchor;
		anchor.x = (size.x) * (anc % 3u) * scale.x;
		anchor.y = (size.y) * (anc / 3u) * scale.y;

		//	���_���W������z�u�����߂�
		element.pos.xy = pos + scale * size * offset_array[i].xy * 2.0f - float2(1.0f, 1.0f);
		//	�A���J�[�̏�񕪂����ʒu�����炷
		element.pos.xy -= anchor;
		//	DirectX��-1���X�N���[����ԉ��Ȃ̂ŁAY���𔽓]����
		element.pos.y *= -1;

		//	XY���ʂȂ̂� z��0�Aw��1
		element.pos.z = 0.0f;
		element.pos.w = 1.0f;

		//	�T�C�Y�ύX����UI��-----------------------------------
		//	--------------------------------------------------

		//	�F���i��������͎g���Ȃ��̂łƂ肠�������j
		element.color = float4(1.0f, 1.0f, 1.0f, 1.0f);

		//	�e�N�X�`����UV���W
		element.tex = offset_array[i].xy;

		output.Append(element);
	}
	output.RestartStrip();
}