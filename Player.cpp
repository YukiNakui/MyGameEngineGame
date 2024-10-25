#include "Player.h"
#include"Engine/FBX.h"
#include"ChildOden.h"
#include"Engine/Input.h"
#include"Engine/Model.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel = Model::Load("Assets/Oden.fbx");
	transform_.position_ = { 0,-3,0 };
	transform_.scale_ = { 0.5,0.5,0.5 };
}

void Player::Update()
{
	transform_.rotate_.y += 1;
	/*if (transform_.rotate_.y > 60 * 10) {
		KillMe();
	}*/

	if (Input::IsKeyDown(DIK_SPACE)) {
		GameObject* pCO = Instantiate<ChildOden>(this);
		pCO->SetPosition(transform_.position_);
		pCO->SetScale(0.2f, 0.2f, 0.2f);
	}
	
	if (Input::IsKey(DIK_LEFTARROW))
		transform_.position_.x-=0.1f;
	if (Input::IsKey(DIK_RIGHTARROW))
		transform_.position_.x+=0.1f;
	if (Input::IsKey(DIK_J))
		transform_.rotate_.z -= 0.5f;
	if (Input::IsKey(DIK_L))
		transform_.rotate_.z += 0.5f;
	if (Input::IsKey(DIK_I))
		transform_.rotate_.x -= 0.5f;
	if (Input::IsKey(DIK_K))
		transform_.rotate_.x += 0.5f;
	if (Input::IsMouseButton(0)) {
		transform_.scale_.x += 0.1f;
		transform_.scale_.y += 0.1f;
		transform_.scale_.z += 0.1f;
	}
	if (Input::IsMouseButton(1)) {
		transform_.scale_.x -= 0.1f;
		transform_.scale_.y -= 0.1f;
		transform_.scale_.z -= 0.1f;
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
	//pOden->Release();
	//delete pOden;
}
