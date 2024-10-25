#include"Model.h"
#include"Direct3D.h"

namespace Model
{
	//ヘッダに書くといろんなところで呼ばれて怒られる cppで追加すると大丈夫
	std::vector<ModelData*> modelList;
}

int Model::Load(std::string filename)
{
	//リストをポインタで作ったのでポインタで作る
	ModelData* pData = new ModelData;
	pData->filename_ = filename; //ヘッダで初期化してるなら書かなくてもよい
	pData->pFBX_ = nullptr;      //ヘッダで初期化してるなら書かなくてもよい
	
	for (auto& e : modelList)
	{
		if (e->filename_ == filename)//読み込み済み
		{
			pData->pFBX_ = e->pFBX_;//すでに読み込んでいるFBXを使う
			break;//同名のファイルが読み込み済み
		}
	}
	if (pData->pFBX_ == nullptr)//リストに同名のファイルがない
	{
		pData->pFBX_ = new FBX;
		pData->pFBX_->Load(filename);//ファイル読み込み
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
	bool isReffered = false;//同じモデルを他でも使っていないか
	for (int j = 0; j < modelList.size(); j++) {
		for (int i = j + 1; i < modelList.size(); i++) {//0から開始するとすでに消している可能性があるのでダメ
			if (modelList[j]->pFBX_ == modelList[i]->pFBX_)//他で使っている
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)//他で使っていない
		{
			SAFE_DELETE(modelList[j]->pFBX_);
		}
		SAFE_DELETE(modelList[j]);
	}
	modelList.clear();
}
