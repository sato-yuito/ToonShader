#pragma once
#include "Engine/GameObject.h"


class Arrow : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Arrow(GameObject* parent);

    //�f�X�g���N�^
    ~Arrow();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

