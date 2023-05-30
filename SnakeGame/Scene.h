#pragma once
#include "CommonInclude.h"
#include "GameObject.h"

#define MAX_OJBECT 256

#define MapY 20
#define MapX 20

int GameObjectCount = 0;
int AppleCount = 0;

class Scene
{
public:
	void Initialize()
	{
		if (mType == eSceneType::Title)
		{
			InitTitleScene();
			//mType = eSceneType::Play;
		}
		else if (mType == eSceneType::Play)
		{
			InitPlayScene();
			//mType = eSceneType::End;
		}
		else if (mType == eSceneType::End)
		{

		}

		//게임 오브젝트 초기화
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Initialize();
		}
	}

	void Update()
	{

		for (size_t i = 0; i < 256; i++)
		{
			if (mGameObjects[i] != nullptr)
			{
				if (mGameObjects[i]->GetType() == eGameObjectType::Apple)
				{
					if (mGameObjects[0]->GetPos().x == mGameObjects[i]->GetPos().x
						&& mGameObjects[0]->GetPos().y == mGameObjects[i]->GetPos().y)
					{
						Node* head = mGameObjects[0]->GetHeadNode();
						AddNode(head, L'◆');


						GOTO_XY((mGameObjects[i]->GetPos().x * 2 + 1 + offsetX), (mGameObjects[i]->GetPos().y + offsetY + 5));
						std::wcout << L' ';
						GOTO_XY((mGameObjects[i]->GetPos().x * 2 + offsetX), (mGameObjects[i]->GetPos().y + offsetY + 5));
						std::wcout << L' ';

						delete mGameObjects[i];
						mGameObjects[i] = nullptr;
					}
				}
			}
		}

		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Update();
		}



	}

	void Render()
	{
		SET_COLOR(COLOR::DARK_SKY_BLUE);
		GOTO_XY(offsetX + 10, (offsetY));		std::wcout << (L"┏━━━━━━━━━━━━━━━━┓");
		GOTO_XY(offsetX + 10, (offsetY + 1));  std::wcout << (L"┃   PLAY SCENE   ┃");
		GOTO_XY(offsetX + 10, (offsetY + 2));   std::wcout << (L"┗━━━━━━━━━━━━━━━━┛");

		for (size_t y = 0; y < MapY; y++)
		{
			for (size_t x = 0; x < MapX; x++)
			{
				SET_COLOR(COLOR::WHITE);
				GOTO_XY((x * 2 + offsetX), (y + offsetY + 5));
				std::wcout << mMap[y][x];
			}

		}

		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Release()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Release();
		}
	}

	void AddGameObject(Vector2 pos, eGameObjectType type)
	{
		GameObject* obj = new GameObject();
		obj->SetPos(pos);
		obj->SetType(type);

		mGameObjects[GameObjectCount] = obj;
		GameObjectCount++;


	}

	void InitTitleScene()
	{
		SET_COLOR(COLOR::DARK_RED);
		GOTO_XY((offsetX + 10), (offsetY + 1));   std::wcout << (L"S N A K E  G A M E");

		SET_COLOR(COLOR::DARK_YELLOW);
		GOTO_XY(offsetX + 10, (offsetY + 2));   std::wcout << (L"┏━━━━━━━━━━━━━━━━┓");
		GOTO_XY(offsetX + 10, (offsetY + 3));   std::wcout << (L"┃ S N A K E  GAME┃");
		GOTO_XY(offsetX + 10, (offsetY + 4));   std::wcout << (L"┃ made by subtle ┃");
		GOTO_XY(offsetX + 10, (offsetY + 5));   std::wcout << (L"┗━━━━━━━━━━━━━━━━┛");

		GOTO_XY(offsetX + 10, (offsetY + 8));   std::wcout << (L"┗━ PRESS  ENTER ━┛");


		int to_add = 0;
		int cur_color = 0;
		while (true)
		{
			GOTO_XY(offsetX + 1, (offsetY + 13));
			for (to_add = 0; to_add < 37; to_add++)
			{
				SET_COLOR((cur_color + to_add % 16 * 16));
				std::wcout << L" ";
			}
			if (cur_color > 0)
				cur_color--;
			else
				cur_color = 15;
			Sleep(100);

			if (_kbhit())
			{
				SET_COLOR(COLOR::BLACK);
				break;
			}
		}
	}

	void InitPlayScene()
	{
		//맵 초기화
		for (size_t i = 0; i < MapY; i++)
		{
			mMap[i][0] = L'□';
			mMap[i][MapX - 1] = L'□';
		}
		for (size_t i = 0; i < MapY; i++)
		{
			mMap[0][i] = L'□';
			mMap[MapY - 1][i] = L'□';
		}


	}

	eSceneType GetType() { return mType; }
	void SetType(eSceneType type) { mType = type; }


private:
	GameObject* mGameObjects[MAX_OJBECT];

	wchar_t mMap[MapY][MapX];
	eSceneType mType;
};

