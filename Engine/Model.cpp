#include"Model.h"
#include"Direct3D.h"

namespace Model
{
	//�w�b�_�ɏ����Ƃ����ȂƂ���ŌĂ΂�ē{���� cpp�Œǉ�����Ƒ��v
	std::vector<ModelData*> modelList;
}

int Model::Load(std::string filename)
{
	//���X�g���|�C���^�ō�����̂Ń|�C���^�ō��
	ModelData* pData = new ModelData;
	pData->filename_ = filename; //�w�b�_�ŏ��������Ă�Ȃ珑���Ȃ��Ă��悢
	pData->pFBX_ = nullptr;      //�w�b�_�ŏ��������Ă�Ȃ珑���Ȃ��Ă��悢
	
	for (auto& e : modelList)
	{
		if (e->filename_ == filename)//�ǂݍ��ݍς�
		{
			pData->pFBX_ = e->pFBX_;//���łɓǂݍ���ł���FBX���g��
			break;//�����̃t�@�C�����ǂݍ��ݍς�
		}
	}
	if (pData->pFBX_ == nullptr)//���X�g�ɓ����̃t�@�C�����Ȃ�
	{
		pData->pFBX_ = new FBX;
		pData->pFBX_->Load(filename);//�t�@�C���ǂݍ���
	}

	modelList.push_back(pData);
	return(modelList.size() - 1);
}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel)
{
	modelList[hModel]->pFBX_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false;//�������f���𑼂ł��g���Ă��Ȃ���
	for (int j = 0; j < modelList.size(); j++) {
		for (int i = j + 1; i < modelList.size(); i++) {//0����J�n����Ƃ��łɏ����Ă���\��������̂Ń_��
			if (modelList[j]->pFBX_ == modelList[i]->pFBX_)//���Ŏg���Ă���
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)//���Ŏg���Ă��Ȃ�
		{
			SAFE_DELETE(modelList[j]->pFBX_);
		}
		SAFE_DELETE(modelList[j]);
	}
	modelList.clear();
}
