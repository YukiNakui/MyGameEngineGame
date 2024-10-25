#pragma once
#include<string>
#include"FBX.h"

namespace Model 
{
	struct ModelData//struct�͂ǂ�����ł��A�N�Z�X�ł���
	{
		FBX* pFBX_;
		Transform transform_;
		std::string filename_;
		ModelData() :pFBX_(nullptr),filename_(""){}//�R���X�g���N�^�ŏ�����
	};
	//���f���̈ꗗ��ۑ�����z��ivector��list?�j
	int Load(std::string filename);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
}