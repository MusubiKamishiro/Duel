// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
    float4 Position : POSITION; // ���W( VERTEX3DSHADER�\���̂� pos �̒l )
    float3 Normal : NORMAL0; // �@��( VERTEX3DSHADER�\���̂� norm �̒l )
    float4 DiffuseColor : COLOR0; // �f�B�t���[�Y�J���[( VERTEX3DSHADER�\���̂� dif �̒l )
    float4 SpecularColor : COLOR1; // �X�y�L�����J���[( VERTEX3DSHADER�\���̂� spc �̒l )
    float2 TextureCoord0 : TEXCOORD0; // �e�N�X�`�����W�O( VERTEX3DSHADER�\���̂� u, v �̒l )
    float2 TextureCoord1 : TEXCOORD1; // �e�N�X�`�����W�P( VERTEX3DSHADER�\���̂� su, sv �̒l )
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
    float4 ProjectionPosition : POSITION; // ���W( �ˉe��� )
    float4 DiffuseColor : COLOR0; // �f�B�t���[�Y�J���[
    float2 TextureCoord0 : TEXCOORD0; // �e�N�X�`�����W
};


// C++ ���Őݒ肷��萔�̒�`
float4x4 cfViewMatrix : register(c6); // ���[���h���W���r���[���W�ɕϊ�����s��̓]�u�s��
float4x4 cfProjectionMatrix : register(c2); // �r���[���W���ˉe���W�ɕϊ�����s��̓]�u�s��

// ���_���W�ɉ��Z����l
float4 cfAddPosition : register(c0);


// main�֐�
VS_OUTPUT main(VS_INPUT VSInput)
{
    VS_OUTPUT VSOutput;
    float4 lWorldPosition;
    float4 lViewPosition;

    // ���͂̒��_���W�ɂb�{�{�v���O�������Őݒ肵�����_���W�����Z����
    lWorldPosition = VSInput.Position + cfAddPosition;

    // ���_���W���r���[��Ԃ̍��W�ɕϊ�����
    lViewPosition = mul(lWorldPosition, cfViewMatrix);

    // �r���[��Ԃ̍��W���ˉe��Ԃ̍��W�ɕϊ�����
    VSOutput.ProjectionPosition = mul(lViewPosition, cfProjectionMatrix);

    // �e�N�X�`�����W�͂��̂܂ܑ��
    VSOutput.TextureCoord0 = VSInput.TextureCoord0;

    // ���_�J���[�͂��̂܂ܑ��
    VSOutput.DiffuseColor = VSInput.DiffuseColor;

    // �֐��̖߂�l���s�N�Z���V�F�[�_�[�ɓn�����
    return VSOutput;
}