#include "ChildOden.h"
#include"Engine/FBX.h"
#include"Engine/Model.h"
#include"Enemy.h"
#include"Engine/SphereCollider.h"

ChildOden::ChildOden(GameObject* parent)
	:GameObject(parent,"ChildOden"),hModel(-1)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	hModel = Model::Load("Assets//Oden.fbx");
	transform_.scale_ = { 0.2,0.2,0.2 };
	//transform_.rotate_.x = 90.0f;
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void ChildOden::Update()
{
	transform_.position_.z+=0.5f;
	transform_.rotate_.x += 10.0f;;
	

	if (transform_.position_.z >= 15.0f) {
		KillMe();
	}
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
}

void ChildOden::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy")
	{
		KillMe();
		pTarget->KillMe();
	}
}
