#include "PlayScene.h"
#include"Player.h"
#include"Enemy.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this);//PlayScene‚ÌŽq‚Æ‚µ‚ÄPlayer‚ðì‚é
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
