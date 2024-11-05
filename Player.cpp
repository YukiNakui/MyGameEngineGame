#include "Player.h"
#include"ChildOden.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
#include"Engine/Camera.h"

namespace {
	const int MAX_HP = 3;
	const int DEFAULT_ROTATE_X = 90.0f;
	const int DEFAULT_ROTATE_Y = 90.0f;
	const int DEFAULT_ROTATE_Z = 90.0f;
	const int MOVE_ROTATE_MAX = 30.0f;
	const float CAN_MOVE_EDGE = 4.0f;
	const float MOVE_SPEED = 0.3f;
	const float ROTATE_SPEED = 2.0f;
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
	transform_.rotate_.z = DEFAULT_ROTATE_Z;
	transform_.rotate_.x = DEFAULT_ROTATE_X;
	transform_.rotate_.y = DEFAULT_ROTATE_Y;
	SphereCollider* col = new SphereCollider(1.0f);//半径0.5のコライダー
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

	if (!isDead) {
		if (Input::IsKeyDown(DIK_SPACE)) {
			GameObject* pCO = Instantiate<ChildOden>(this);
			pCO->SetPosition(transform_.position_);
			pCO->SetScale(0.2f, 0.2f, 0.2f);
			pCO->SetRotateZ(DEFAULT_ROTATE_Z);
			pCO->SetRotateY(DEFAULT_ROTATE_Y);
		}

		if (Input::IsKey(DIK_LEFTARROW)) {
			if (transform_.position_.x >= -CAN_MOVE_EDGE)
				transform_.position_.x -= MOVE_SPEED;
			if (transform_.rotate_.x > DEFAULT_ROTATE_X - MOVE_ROTATE_MAX)
				transform_.rotate_.x -= ROTATE_SPEED;
		}
		else if (Input::IsKey(DIK_RIGHTARROW)) {
			if (transform_.position_.x <= CAN_MOVE_EDGE)
				transform_.position_.x += MOVE_SPEED;
			if (transform_.rotate_.x < DEFAULT_ROTATE_X + MOVE_ROTATE_MAX)
				transform_.rotate_.x += ROTATE_SPEED;
		}
		else {
			if (transform_.rotate_.x < DEFAULT_ROTATE_X)
				transform_.rotate_.x++;
			if (transform_.rotate_.x > DEFAULT_ROTATE_X)
				transform_.rotate_.x--;
		}
		
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