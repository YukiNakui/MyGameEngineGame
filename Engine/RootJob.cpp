#include "RootJob.h"
#include"./SceneManager.h"

RootJob::RootJob(GameObject *parent)
	:GameObject(parent,"RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{	//PlayScene�N���X��GameObject���p��
	/*PlayScene* pPlayScene;
	pPlayScene = new PlayScene(this);
	pPlayScene->Initialize();
	childList_.push_back(pPlayScene);*/
	Instantiate<SceneManager>(this);
	//��������SceneManager�ɒu�������āA�V�[��������s������
}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}
