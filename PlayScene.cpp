#include "PlayScene.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"Engine/Direct3D.h"

const int RESPAWN_TIME = 1.5;

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),pPlayer(nullptr),pEnemy(nullptr),pCDTimer(nullptr),pGOPict(nullptr),
	startCountTime(3.0f)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	pPlayer = Instantiate<Player>(this);
	//pEnemy = Instantiate<Enemy>(this);
	pCDTimer = Instantiate<CDTimer>(this);
	pCDTimer->SetInitTime(startCountTime);
	pGOPict = new Sprite;
	pGOPict->Load("Assets/YOUEATEN.png");
	transform_.scale_.y = 0.5f;
}

void PlayScene::Update()
{
	if (pCDTimer->IsTimeOver()) {
		//isStartCountNow = false;
		//pCDTimer->SetInitTime(RESPAWN_TIME);
		if (!pPlayer->IsPlayerDead()) {
			pEnemy = Instantiate<Enemy>(this);
			pCDTimer->SetInitTime(RESPAWN_TIME);
		}
		//pCDTimer->ResetTimer();
	}

	if (pPlayer->IsPlayerDead()) {
		if (Input::IsKeyDown(DIK_RETURN)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
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
