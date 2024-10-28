#include "TitleScene.h"
#include"Player.h"
#include"OdenTitle.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene")
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<OdenTitle>(this);
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}
