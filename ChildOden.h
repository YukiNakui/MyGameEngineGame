#pragma once
#include "Engine/GameObject.h"

class ChildOden :
    public GameObject
{
	int hModel;
public:
	ChildOden(GameObject* parent);
	~ChildOden();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void OnCollision(GameObject* pTarget) override;
};

