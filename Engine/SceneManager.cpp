#include "SceneManager.h"
#include"../TitleScene.h"
#include"../PlayScene.h"
#include"Direct3D.h"
#include"Model.h"

SceneManager::SceneManager(GameObject* parent)
    :GameObject(parent,"SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
    //���̃V�[�������݂̃V�[���ƈႤ �� �V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
    if (currentSceneID_ != nextSceneID_)
    {
        //���̃V�[���̃I�u�W�F�N�g��S�폜�i�q�I�u�W�F�N�g��S�폜�j
        auto scene = childList_.begin();//�؂�ւ���O�̃V�[�����擾
        (*scene)->ReleaseSub();//�V�[���̎q��������
        SAFE_DELETE(*scene);//�V�[��������
        childList_.clear();//�����Ă郊�X�g������
        Model::Release();

        //���[�h�����f�[�^��S�폜

        //���̃V�[�����쐬
        switch (nextSceneID_)
        {
        case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
        case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
        }
        //�����V�[���𐶐��o������A�J�����g�V�[�����X�V
        currentSceneID_ = nextSceneID_;
    }
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
