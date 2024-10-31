#pragma once
#include<string>
#include<list>
#include"Transform.h"

class SphereCollider;

class GameObject
{
	bool isDead_;//����
protected:
	std::list<GameObject*> childList_;
	Transform	           transform_;
	GameObject*            pParent_;
	std::string	           objectName_;
	SphereCollider*		   pCollider_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	void KillMe();

	//inline��`
	void SetPosition(XMFLOAT3 position) {transform_.position_ = position;}
	void SetPosition(float x, float y, float z) {SetPosition(XMFLOAT3(x, y, z));}
	void SetScale(float sx, float sy, float sz) {transform_.scale_ = { sx,sy,sz };}
	void SetRotateX(float xrotate) {transform_.rotate_.x = xrotate;}
	void SetRotateY(float yrotate) {transform_.rotate_.y = yrotate;}
	void SetRotateZ(float zrotate) {transform_.rotate_.z = zrotate;}

	GameObject* FindObject(std::string objName);
	GameObject* GetRootJob();
	GameObject* FindChildObject(std::string objName);

	//�I�u�W�F�N�g�̖��O���擾
    //�ߒl�F���O
	const std::string& GetObjectName(void) const;
	
	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);
	virtual void OnCollision(GameObject* pTarget) {};

	//template<typename T> �Ɠ���
	template <class T>
	T* Instantiate(GameObject* pParent)
	{
		T* pTmp = new T(pParent);//������e�ɂ��Ďq�N���X�̃I�u�W�F�N�g�����
		if (pTmp != nullptr)
		{
			pTmp->Initialize();//������
			childList_.push_back(pTmp);//�q�N���X�����郊�X�g�ɒǉ�
		}
		return pTmp;
	}
};

