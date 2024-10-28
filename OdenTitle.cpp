#include "OdenTitle.h"
#include"Engine/FBX.h"
#include"Engine/Input.h"
#include"Engine/Model.h"

OdenTitle::OdenTitle(GameObject* parent)
	:GameObject(parent,"OdenTitle"),hModel(-1)
{
}

OdenTitle::~OdenTitle()
{
}

void OdenTitle::Initialize()
{
	hModel = Model::Load("Assets/OdenTitle.fbx");
	/*transform_.scale_.x = 8.0f;
	transform_.scale_.y = 6.0f;*/
}

void OdenTitle::Update()
{
}

void OdenTitle::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void OdenTitle::Release()
{
}
