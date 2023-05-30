#pragma once
#include "Scene.h"


class Application
{
public:
	void Initialize()
	{
		bEnable = true;
		mScenes[(UINT)eSceneType::Title].SetType(eSceneType::Title);
		mScenes[(UINT)eSceneType::Play].SetType(eSceneType::Play);
		mScenes[(UINT)eSceneType::End].SetType(eSceneType::End);

		mPlayScene = &mScenes[(UINT)eSceneType::Title];

		mScenes[(UINT)eSceneType::Play].AddGameObject(Vector2{ 5, 5 }, eGameObjectType::Snake);
		//mScenes[(UINT)eSceneType::Play].AddGameObject(Vector2{ 10, 10 }, eGameObjectType::Apple);

		mScenes[(UINT)eSceneType::Title].Initialize();;
		mScenes[(UINT)eSceneType::Play].Initialize();
		mScenes[(UINT)eSceneType::End].Initialize();
	}

	void Run()
	{
		int cnt = 0;
		while (bEnable)
		{
			eSceneType type = mPlayScene->GetType();
			if (type == eSceneType::Title)
			{
				if (_kbhit())
				{
					system("cls");
					//system("color 0");
					mPlayScene = &mScenes[(UINT)eSceneType::Play];
				}
			}
			else if (type == eSceneType::Play)
			{

			}
			else if (type == eSceneType::End)
			{

			}
			if (cnt == 10)
			{
				int y = rand() % 19 + 1;
				int x = rand() % 19 + 1;
				mScenes[(UINT)eSceneType::Play].AddGameObject(Vector2{ x, y }, eGameObjectType::Apple);
				cnt = 0;
			}

			cnt++;
			Sleep(500);
			mPlayScene->Update();
			mPlayScene->Render();
		}
	}

	void Update()
	{

	}

	void Render()
	{

	}

	void Release()
	{
		for (Scene scene : mScenes)
		{
			scene.Release();
		}
	}

private:
	bool bEnable;
	Scene mScenes[(UINT)eSceneType::Max];
	Scene* mPlayScene;
};