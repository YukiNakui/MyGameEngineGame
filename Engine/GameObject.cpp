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
	if (parent != nullptr)//親があったら
		this->transform_.pParent_ = &(parent->transform_);//親のトランスフォームのアドレスをトランスフォームに入れる
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();//子オブジェクトのUpdateを呼ぶ
	}
	//オブジェクトを消すのとリストを消すのは勝手が違う
	for (auto itr = childList_.begin(); itr != childList_.end();) {
		if ((*itr)->isDead_) {
			(*itr)->ReleaseSub();
			//(*itr)->Release();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);//消したとこはスキップ
		}
		else
			itr++;
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr : childList_) {
		itr->DrawSub();//子オブジェクトのDrawを呼ぶ
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr : childList_) {
		itr->ReleaseSub();//子オブジェクトのReleaseを呼ぶ
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindObject(std::string objName)
{
	//自分から見て、ルートジョブを探して、
	//そのルートジョブから全部の子をたどってobjNameを探す
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(objName);
	return(result);
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;
	//再起呼び出し（親をたどってく）
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindChildObject(std::string objName)
{
	if (this->objectName_ == objName) {//見つかったら
		return this;
	}
	else {
		for (auto itr : childList_) {//子オブジェクトをたどってく
			GameObject* obj = itr->FindChildObject(objName);
			if (obj != nullptr)
				return obj;
		}
	}
	//見つからなかったらnullptrを返す
	return nullptr;
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	//pColliderがnullptrか自分自身をみているときはreturn
	if (this->pCollider_ == nullptr || pTarget->pCollider_ == nullptr || this == pTarget)
		return;
	//自分とターゲットのコライダー同士の当たり判定を書く
	XMVECTOR p1 = XMLoadFloat3(&(this->transform_.position_));
	XMVECTOR p2 = XMLoadFloat3(&(pTarget->transform_.position_));
	XMVECTOR d = XMVector3Length(p1 - p2);
	float dist = XMVectorGetX(d);                      //自分とターゲットの距離
	float rDist = this->pCollider_->GetRadius() + 
				  pTarget->pCollider_->GetRadius();    //自分とターゲットの半径の和 
	if (dist <= rDist)//2点間の距離＜＝半径の和
	{	//当たっているときの処理
		OnCollision(pTarget);
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{   //自分とターゲットの当たり判定
	
	if (this->pCollider_ == nullptr)
		return;

	if (pTarget->pCollider_ != nullptr)
		Collision(pTarget);
	
	//自分とターゲットの子オブジェクト全部の当たり判定（再帰）
	for (auto& itr : pTarget->childList_) {
		RoundRobin(itr);
	}
}
