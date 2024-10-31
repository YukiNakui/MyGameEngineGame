#include "Enemy.h"
#include"Engine/FBX.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel = Model::Load("Assets/Enemy.fbx");
	transform_.position_ = { 0.0f,-3.0f,10.0f };
	transform_.rotate_.y = 180.0f;
	transform_.scale_ = { 0.5f,0.5f,0.5f };
	SphereCollider* col = new SphereCollider(0.1f);//���a0.1�̃R���C�_�[
	this->AddCollider(col);//�R���C�_�[���A�^�b�`
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
