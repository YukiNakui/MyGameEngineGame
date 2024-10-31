#include "PlayScene.h"
#include"Engine/Direct3D.h"

const int RESPAWN_TIME = 1.0;

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),pPlayer(nullptr),pEnemy(nullptr),pCDTimer(nullptr),pGOPict(nullptr)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	pPlayer = Instantiate<Player>(this);
	pEnemy = Instantiate<Enemy>(this);
	pCDTimer = Instantiate<CDTimer>(this);
	pCDTimer->SetInitTime(RESPAWN_TIME);
	pGOPict = new Sprite;
	pGOPict->Load("Assets/YOUEATEN.png");
	transform_.scale_.y = 0.5f;
}

void PlayScene::Update()
{
	if (pCDTimer->IsTimeOver()) {
		pEnemy = Instantiate<Enemy>(this);
		pCDTimer->ResetTimer();
	}
}

void PlayScene::Draw()
{
	if (pPlayer->IsPlayerDead()) {
		pGOPict->Draw(transform_);
	}
}

void PlayScene::Release()
{
	//SAFE_DELETE(pPlayer);
	//SAFE_DELETE(pEnemy);
	//SAFE_DELETE(pCDTimer);
}
