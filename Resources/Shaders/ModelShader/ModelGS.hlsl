#include "ModelShader.hlsli"
//	���_�̐���萔�Ƃ��ėp�ӂ��Ă���
static const int vnum = 3;


[maxvertexcount(vnum)]
void main(
	triangle VS_OUT input[3],
	inout TriangleStream<PS_IN> output
)
{
	//	���͂Ƃ��ēn���ꂽ���_1�ɑ΂��āA4�ɑ��₷��Ƃ��s��
    for (int i = 0; i < 3; i++)
    {
        PS_IN element;
		
		//	���_�V�F�[�_���o�͂������W�ɁA���B������|���S����i�Ԗڂ̍��W���v�Z����
        element.Posw = mul(input[i].Pos, matWorld);

		//	��L�̌��ʂɁA�r���[�s����|���Z����
        element.Pos = mul(element.Posw, matView);
		//	��L�̌��ʂɁA�v���W�F�N�V�����s����|���Z����
        element.Pos = mul(element.Pos, matProj);
        // ���[���h���W�̖@�����v�Z
        element.Norw = mul(input[i].Nor, matWorld);
		//	�|���S���ɕ\������e�N�X�`����UV�����Z�o����		
        element.Tex = input[i].Tex;

		
		//	�X�g���[���֒��_����ǉ�����		
        output.Append(element);
    }
	
	//	�ǉ���������K�؂ɏ������āA���̃V�F�[�_�֓n����悤�ɍč\������B
	//	�����TriangleStream�ƂȂ邽�߁A�O�p�`�|���S���p�̒��_�f�[�^�Ƃ��Ď��̃V�F�[�_�փf�[�^���n����悤�A
	//	�ǂ������ɏ��������
	//	������ȍ~��Append�Œǉ����Ă��A����܂ł̎O�p�`�|���S���Ƃ͕ʂ́u�O���[�v�v�̃|���S���ƂȂ��Ă��܂�
    output.RestartStrip();
}
