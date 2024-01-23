//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

Texture2D       toon_texture:register(t1);
//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global:register(b0)
{
	float4x4	matWVP;			       // ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4    matW;                 //���[���h�s��
	float4x4	matNormal;           // ���[���h�s��
	float4		diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4     ambient;
	float4     speculer;
	float     shininess;
	bool		isTexture;		   // �e�N�X�`���\���Ă��邩�ǂ���
};

cbuffer global:register(b1)
{
	float4      lightPos;           //���C�g�̈ʒu
	float4       eyePos;           //���_

};
//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos  : SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;		//UV���W
	float4 color	: COLOR;	//�F�i���邳�j
	float4 eyev  :  POSITION;
	float4 normal : NORMAL;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	VS_OUT outData = (VS_OUT)0;
	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	
	normal.w = 0;
	pos = pos + normal * 0.05f;
	outData.pos =mul(pos, matWVP);
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{

	return (0,0,0,0);
   
   
	
	
}