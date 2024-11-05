#include "PlayScene.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"
#include"Engine/Direct3D.h"

namespace {
	const float RESPAWN_TIME = 1.5f;
	const float READY_TYME = 1.5f;
	const float GO_TYME = 1.5f;
}

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),pPlayer(nullptr),pEnemy(nullptr),pCDTimer(nullptr),
	pGameOverPict(nullptr),pReadyPict(nullptr),pGoPict(nullptr),state(READY)
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
	pCDTimer->SetInitTime(READY_TYME);
	pGameOverPict = new Sprite;
	pGameOverPict->Load("Assets/YOUEATEN.png");
	pReadyPict = new Sprite;
	pReadyPict->Load("Assets/READY.png");
	pGoPict = new Sprite;
	pGoPict->Load("Assets/GO.png");
	gameOverTrs.scale_.y = 0.1f;
	readyTrs.scale_.y = 0.5f;
	goTrs.scale_.y = 0.5f;
}

void PlayScene::Update()
{
	if (pCDTimer->IsTimeOver()) {
		if (!pPlayer->IsPlayerDead()) {
			switch (state)
			{
			case PlayScene::READY:
				state = GO;
				pCDTimer->SetInitTime(GO_TYME);
				break;
			case PlayScene::GO:
				state = PLAY;
				pCDTimer->SetInitTime(RESPAWN_TIME);
				break;
			case PlayScene::PLAY:
				pEnemy = Instantiate<Enemy>(this);
				pCDTimer->ResetTimer();
				break;
			default:
				break;
			}
		}
	}

	if (pPlayer->IsPlayerDead()) {
		if (gameOverTrs.scale_.y < 0.5f)
			gameOverTrs.scale_.y += 0.01f;
		if (Input::IsKeyDown(DIK_RETURN)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
	}
}

void PlayScene::Draw()
{
	switch (state)
	{
	case PlayScene::READY:
		pReadyPict->Draw(readyTrs);
		break;
	case PlayScene::GO:
		pGoPict->Draw(goTrs);
		break;
	case PlayScene::PLAY:
		break;
	default:
		break;
	}
	if (pPlayer->IsPlayerDead()) {
		pGameOverPict->Draw(gameOverTrs);
	}
}

void PlayScene::Release()
{
}
