#pragma once
#include "Engine/GameObject.h"
#include"Player.h"
#include"Enemy.h"
#include"CDTimer.h"
#include"Engine/Sprite.h"

class PlayScene :
    public GameObject
{
	enum STATE {
		READY,
		GO,
		PLAY
	};
	STATE state;

	Player* pPlayer;
	Enemy* pEnemy;
	CDTimer* pCDTimer;
	Sprite* pGameOverPict;
	Sprite* pReadyPict;
	Sprite* pGoPict;

	Transform readyTrs;
	Transform goTrs;
public:
	PlayScene(GameObject* parent);
	~PlayScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

