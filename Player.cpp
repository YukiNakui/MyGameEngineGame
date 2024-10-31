#include "Player.h"
#include"ChildOden.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"

namespace {
	const int MAX_HP = 3;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel{-1}, HP(MAX_HP),isDead(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	string fileName[ODEN_STATE::MAX] = { "OdenStick", "OdenTikuwa","OdenDaikonTikuwa","Oden" };
	for (int i = 0; i < ODEN_STATE::MAX; i++) {
		hModel[i] = Model::Load("Assets/" + fileName[i] + ".fbx");
		assert(hModel[i] >= 0);
	}
	transform_.position_ = { 0,-3,0 };
	transform_.scale_ = { 0.5,0.5,0.5 };
	transform_.rotate_.x = 90.0f;
	SphereCollider* col = new SphereCollider(0.5f);//半径0.5のコライダー
	this->AddCollider(col);//コライダーをアタッチ
}

void Player::Update()
{
	if (HP <= 0)
		isDead = true;

	float rad = 0.1f;
	static int time = 0.0f;
	time ++;
	transform_.position_.y = sinf(1 - (time/30.0f)) * rad - 3.0f;

	if (Input::IsKeyDown(DIK_SPACE)) {
		GameObject* pCO = Instantiate<ChildOden>(this);
		pCO->SetPosition(transform_.position_);
		pCO->SetScale(0.2f, 0.2f, 0.2f);
		pCO->SetRotateZ(90.0f);
		pCO->SetRotateY(90.0f);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel[HP], transform_);
	Model::Draw(hModel[HP]);
}

void Player::Release()
{
	//pOden->Release();
	//delete pOden;
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy")
	{
		if (HP > 0)
			HP--;
		pTarget->KillMe();
	}
}