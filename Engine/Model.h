#pragma once
#include<string>
#include"FBX.h"

namespace Model 
{
	struct ModelData//structはどこからでもアクセスできる
	{
		FBX* pFBX_;
		Transform transform_;
		std::string filename_;
		ModelData() :pFBX_(nullptr),filename_(""){}//コンストラクタで初期化
	};
	//モデルの一覧を保存する配列（vectorかlist?）
	int Load(std::string filename);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
}