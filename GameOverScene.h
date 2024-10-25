#pragma once
#include "Engine/GameObject.h"

class GameOverScene :
    public GameObject
{
	int hPict_;
public:
	GameOverScene(GameObject* parent);
	~GameOverScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

