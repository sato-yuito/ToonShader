#include "SceneManager.h"
#include"Model.h"
#include "Direct3D.h"
#include"../TestScene.h"



using namespace Direct3D;

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentScneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentScneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//�V�[�������ۂɐ؂�ւ���
	//���̃V�[����next�V�[�����ʂ�������؂�ւ�
	if (currentScneID_ != nextSceneID_)
	{
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//���[�h�����f�[�^��S���폜
		Model::Release();
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		}
		currentScneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// �w�肵���V�[����nextSceneID_�ɑ������
/// </summary>
/// <param name="_next"></param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}
