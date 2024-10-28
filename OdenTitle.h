#pragma once
#include "Engine/GameObject.h"
class OdenTitle :
    public GameObject
{
	int hModel;
public:
	OdenTitle(GameObject* parent);
	~OdenTitle();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

