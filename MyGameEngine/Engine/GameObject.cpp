#include "GameObject.h"
#include "Direct3D.h"
#include <DirectXTex.h>
#include"SphereCollider.h"
GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),dead_(false),pCollider_(nullptr)
{
	if (pParent_ )
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::KillMe()
{
	dead_ = true;
}

void GameObject::Initialize()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}

void GameObject::Release()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->UpdateSub();

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->dead_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
	
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
	Release();
}


GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		//������_objName�̃I�u�W�F�N�g��������
		return(this);
	}
	else
	{
		for (auto itr:childList_)
		{
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}

/// <summary>
/// �ċN�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>RootJob�̃A�h���X(GameObject *�^)</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

/// <summary>
/// �����蔻��
/// </summary>
/// <param name="pTarget"></param>
void GameObject::Collision(GameObject* pTarget)
{
	//�����̃R���C�_�[�ƃ^�[�Q�b�g���Ԃ����Ă���Ƃ�nullptr
	if ( pTarget == this || pTarget->pCollider_ == nullptr)
		return;

	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x) +
		(transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y) +
		(transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());
	if (dist <= rDist)
	{
		onCollision(pTarget);
		//double p = 0;
	}
}

/// <summary>
/// ��������
/// </summary>
/// <param name="pTarget"></param>
void GameObject::RoundRobin(GameObject* pTarget)
{
	if (pCollider_ == nullptr)
		return;
	if (pTarget->pCollider_ != nullptr)
		Collision(pTarget);
	//�q���O���ƃ^�[�Q�b�g�̐��������[�v
	for (auto itr : pTarget->childList_)
		RoundRobin(itr);
}
