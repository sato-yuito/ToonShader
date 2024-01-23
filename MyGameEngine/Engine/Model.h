#pragma once
#include"Fbx.h"
#include"Transform.h"
#include"Texture.h"
#include<string>
#include<vector>

using std::string;
using std::vector;

namespace Model
{
	struct ModelData
	{
		//FBX
		Fbx *fbx_;

		//�g�����X�t�H�[��
		Transform transform_;
		//�t�@�C����
		string filename_;
	};

	int Load(string filename);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
};

