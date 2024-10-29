#include "TitleScene.h"

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
}

void TitleScene::Draw()
{
	pTitlePict->Draw(transform_);
}

void TitleScene::Release()
{
}
