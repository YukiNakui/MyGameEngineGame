#include "GameObject.h"
#include"Direct3D.h"
#include"./SphereCollider.h"

GameObject::GameObject()
	:pParent_(), objectName_(), isDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),isDead_(false),pCollider_(nullptr)
{
	if (parent != nullptr)//�e����������
		this->transform_.pParent_ = &(parent->transform_);//�e�̃g�����X�t�H�[���̃A�h���X���g�����X�t�H�[���ɓ����
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();//�q�I�u�W�F�N�g��Update���Ă�
	}
	//�I�u�W�F�N�g�������̂ƃ��X�g�������̂͏��肪�Ⴄ
	for (auto itr = childList_.begin(); itr != childList_.end();) {
		if ((*itr)->isDead_) {
			(*itr)->ReleaseSub();
			//(*itr)->Release();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);//�������Ƃ��̓X�L�b�v
		}
		else
			itr++;
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr : childList_) {
		itr->DrawSub();//�q�I�u�W�F�N�g��Draw���Ă�
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr : childList_) {
		itr->ReleaseSub();//�q�I�u�W�F�N�g��Release���Ă�
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindObject(std::string objName)
{
	//�������猩�āA���[�g�W���u��T���āA
	//���̃��[�g�W���u����S���̎q�����ǂ���objName��T��
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(objName);
	return(result);
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;
	//�ċN�Ăяo���i�e�����ǂ��Ă��j
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindChildObject(std::string objName)
{
	if (this->objectName_ == objName) {//����������
		return this;
	}
	else {
		for (auto itr : childList_) {//�q�I�u�W�F�N�g�����ǂ��Ă�
			GameObject* obj = itr->FindChildObject(objName);
			if (obj != nullptr)
				return obj;
		}
	}
	//������Ȃ�������nullptr��Ԃ�
	return nullptr;
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	//pCollider��nullptr���������g���݂Ă���Ƃ���return
	if (this->pCollider_ == nullptr || pTarget->pCollider_ == nullptr || this == pTarget)
		return;
	//�����ƃ^�[�Q�b�g�̃R���C�_�[���m�̓����蔻�������
	XMVECTOR p1 = XMLoadFloat3(&(this->transform_.position_));
	XMVECTOR p2 = XMLoadFloat3(&(pTarget->transform_.position_));
	XMVECTOR d = XMVector3Length(p1 - p2);
	float dist = XMVectorGetX(d);                      //�����ƃ^�[�Q�b�g�̋���
	float rDist = this->pCollider_->GetRadius() + 
				  pTarget->pCollider_->GetRadius();    //�����ƃ^�[�Q�b�g�̔��a�̘a 
	if (dist <= rDist)//2�_�Ԃ̋����������a�̘a
	{	//�������Ă���Ƃ��̏���
		OnCollision(pTarget);
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{   //�����ƃ^�[�Q�b�g�̓����蔻��
	
	if (this->pCollider_ == nullptr)
		return;

	if (pTarget->pCollider_ != nullptr)
		Collision(pTarget);
	
	//�����ƃ^�[�Q�b�g�̎q�I�u�W�F�N�g�S���̓����蔻��i�ċA�j
	for (auto& itr : pTarget->childList_) {
		RoundRobin(itr);
	}
}
