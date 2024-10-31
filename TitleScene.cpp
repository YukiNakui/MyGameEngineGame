#include "TitleScene.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),pTitlePict(nullptr)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	pTitlePict = new Sprite;
	pTitlePict->Load("Assets/ODEN_TITLE.png");
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	pTitlePict->Draw(transform_);
}

void TitleScene::Release()
{
}
