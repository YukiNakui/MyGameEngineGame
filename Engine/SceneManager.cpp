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
    //次のシーンが現在のシーンと違う ＝ シーンを切り替えなければならない
    if (currentSceneID_ != nextSceneID_)
    {
        //そのシーンのオブジェクトを全削除（子オブジェクトを全削除）
        auto scene = childList_.begin();//切り替える前のシーンを取得
        (*scene)->ReleaseSub();//シーンの子供を消す
        SAFE_DELETE(*scene);//シーンを消す
        childList_.clear();//入ってるリストを消す
        Model::Release();

        //ロードしたデータを全削除

        //次のシーンを作成
        switch (nextSceneID_)
        {
        case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
        case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
        }
        //無事シーンを生成出来たら、カレントシーンを更新
        currentSceneID_ = nextSceneID_;
    }
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
