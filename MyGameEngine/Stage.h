#pragma once
#include "Engine/GameObject.h"
#include <d3d11.h>

struct CBUFF_STAGESCENE
{
    XMFLOAT4 lightPos;
    XMFLOAT4 eyePos;
};

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
    int hLightBall_;

    Transform trLightBall;

    ID3D11Buffer* pCBStageScene_;
    void InitConstantBuffer();
    XMFLOAT4 lightSorcePosition;
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetLightPos(XMFLOAT4& _pos) { lightSorcePosition = _pos; }
    XMFLOAT4 GetLightPos() { return(lightSorcePosition); }
};

