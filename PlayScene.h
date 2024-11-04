#pragma once
#include "Engine/GameObject.h"
#include"Player.h"
#include"Enemy.h"
#include"CDTimer.h"
#include"Engine/Sprite.h"

class PlayScene :
    public GameObject
{
	Player* pPlayer;
	Enemy* pEnemy;
	CDTimer* pCDTimer;
	Sprite* pGOPict;
	float startCountTime;
	//bool isStartCountNow;
public:
	PlayScene(GameObject* parent);
	~PlayScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

