#include "Transform.h"

Transform::Transform(): 
    matTranslate_(XMMatrixIdentity()),
matRotate_(XMMatrixIdentity()),
matScale_(XMMatrixIdentity()),
position_(XMFLOAT3(0, 0, 0)),
rotate_(XMFLOAT3(0, 0, 0)),
scale_(XMFLOAT3(1, 1, 1))
{
    
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    //�ړ��s��
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

    //��]�s��
    XMMATRIX rotate_X, rotate_Y, rotate_Z;
    rotate_X = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
    rotate_Y = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
    rotate_Z = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
    matRotate_ = rotate_Z * rotate_X * rotate_Y;

    //�g��s��
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    if (pParent_ != nullptr)
    {
        //�e����������e�̂��߂�WorldMatrix��������
        return matScale_ * matRotate_ * matTranslate_* pParent_->GetWorldMatrix();
    }
    else
    return matScale_* matRotate_* matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
    return  matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
