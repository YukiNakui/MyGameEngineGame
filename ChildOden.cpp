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
	transform_.position_.x = 0.0f;
	transform_.position_.y = 3.0f;
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void ChildOden::Update()
{
	transform_.position_.y+=0.5f;
	transform_.rotate_.y++;
	
	Enemy* enemy = (Enemy*)FindObject("Enemy");
	/*XMFLOAT3 p1 = enemy->GetPosition();
	XMFLOAT3 p2 = transform_.position_;
	float r1 = 0.1f;
	float r2 = 0.5f;
	float dist = (p1.x - p2.x) * (p1.x - p2.x)
			   + (p1.y - p2.y) * (p1.y - p2.y)
			   + (p1.z - p2.z) * (p1.z - p2.z);
	if (dist <= r1 + r2)
	{
		KillMe();
	}*/

	if (transform_.position_.y >= 10.0f) {
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
	KillMe();
	pTarget->KillMe();
}
