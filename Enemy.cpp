#include "Enemy.h"
#include"Engine/FBX.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
#include <random>
#include <time.h>

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	srand((unsigned int)time(NULL));

	hModel = Model::Load("Assets/Enemy.fbx");

	float xPos = rand() % 9 - 4;//-4～4のランダムなx座標を指定

	transform_.position_ = { xPos,-3.0f,20.0f };
	transform_.rotate_.y = 180.0f;
	transform_.scale_ = { 0.5f,0.5f,0.5f };
	SphereCollider* col = new SphereCollider(0.5f);//半径0.1のコライダー
	this->AddCollider(col);//コライダーをアタッチ
}

void Enemy::Update()
{
	transform_.position_.z -= 0.5f;
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}
