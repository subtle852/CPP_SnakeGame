#pragma once
#include "CommonInclude.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


class GameObject
{
public:
	enum class eDirection
	{
		Right,
		Left,
		Up,
		Down,
	};

	void Initialize()
	{
		//mCh = L'●';
		mHead = new Node();
		mHead->ch = L'◆';
		mHead->next = nullptr;
		mHead->prev = nullptr;

		mHead->prevX = mPos.x;
		mHead->prevY = mPos.y;

		mDir = eDirection::Right;
	}
	void Update()
	{


		if (mType == eGameObjectType::Snake)
		{
			char c;
			if (_kbhit()) //키보드 입력 확인 (true / false)
			{
				c = _getch();   // 방향키 입력시 224 00이 들어오게 되기에 앞에 있는 값 224를 없앰
				if (c == -32)	// -32로 입력되면
				{
					c = _getch();  // 새로 입력값을 판별하여 상하좌우 출력
					if (LEFT == c)
					{
						mDir = eDirection::Left;
					}
					else if (RIGHT == c)
					{
						mDir = eDirection::Right;
					}
					else if (UP == c)
					{
						mDir = eDirection::Up;
					}
					else if (DOWN == c)
					{
						mDir = eDirection::Down;
					}
				}
			}

			if (mDir == eDirection::Right)
			{
				RenderClear();
				mHead->prevX = mPos.x;
				mHead->prevY = mPos.y;

				mPos.x++;
				mHead->x = mPos.x;
				mHead->y = mPos.y;

				Node* head = mHead;
				while (head->next != nullptr)
				{
					head->next->prevX = head->next->x;
					head->next->prevY = head->next->y;

					head->next->x = head->next->prev->prevX;
					head->next->y = head->next->prev->prevY;

					head = head->next;
				}
			}
			else if (mDir == eDirection::Left)
			{
				RenderClear();
				mHead->prevX = mPos.x;
				mHead->prevY = mPos.y;
				mPos.x--;

				mHead->x = mPos.x;
				mHead->y = mPos.y;

				Node* head = mHead;
				while (head->next != nullptr)
				{
					head->next->prevX = head->next->x;
					head->next->prevY = head->next->y;

					head->next->x = head->next->prev->prevX;
					head->next->y = head->next->prev->prevY;

					head = head->next;
				}
			}
			else if (mDir == eDirection::Down)
			{
				RenderClear();
				mHead->prevX = mPos.x;
				mHead->prevY = mPos.y;
				mPos.y++;

				mHead->x = mPos.x;
				mHead->y = mPos.y;

				Node* head = mHead;
				while (head->next != nullptr)
				{
					head->next->prevX = head->next->x;
					head->next->prevY = head->next->y;

					head->next->x = head->next->prev->prevX;
					head->next->y = head->next->prev->prevY;

					head = head->next;
				}
			}
			else if (mDir == eDirection::Up)
			{
				RenderClear();
				mHead->prevX = mPos.x;
				mHead->prevY = mPos.y;
				mPos.y--;

				mHead->x = mPos.x;
				mHead->y = mPos.y;

				Node* head = mHead;
				while (head->next != nullptr)
				{
					head->next->prevX = head->next->x;
					head->next->prevY = head->next->y;

					head->next->x = head->next->prev->prevX;
					head->next->y = head->next->prev->prevY;

					head = head->next;
				}
			}
		}
		else // 사과
		{

		}
	}
	void Render()
	{
		if (mType == eGameObjectType::Snake)
		{
			Node* pNode = mHead;
			int randColor = (rand() % 13) + 1;
			SET_COLOR((COLOR)randColor);

			GOTO_XY((mHead->x * 2 + offsetX), (mHead->y + offsetY + 5));
			std::wcout << pNode->ch;
			pNode = pNode->next;

			while (pNode != nullptr)
			{
				int randColor = (rand() % 13) + 1;
				SET_COLOR((COLOR)randColor);

				GOTO_XY((pNode->prev->prevX * 2 + offsetX), (pNode->prev->prevY + offsetY + 5));
				std::wcout << pNode->ch;
				pNode = pNode->next;
			}


		}
		else
		{
			SET_COLOR(COLOR::RED);
			GOTO_XY((mPos.x * 2 + offsetX), (mPos.y + offsetY + 5));
			std::wcout << L'♥';
		}
	}

	void Release()
	{
		delete mHead;
		mHead = nullptr;
	}

	void SetPos(Vector2 pos) { mPos = pos; }
	Vector2 GetPos() { return mPos; }

	void RenderClear()
	{
		Node* pNode = mHead;
		while (pNode != nullptr)
		{
			GOTO_XY((pNode->x * 2 + 1 + offsetX), (pNode->y + offsetY + 5));
			std::wcout << L' ';
			GOTO_XY((pNode->x * 2 + offsetX), (pNode->y + offsetY + 5));
			std::wcout << L' ';
			pNode = pNode->next;
		}
	}

	void SetType(eGameObjectType type) { mType = type; }
	eGameObjectType GetType() { return mType; }


	Node* GetHeadNode() { return mHead; }
private:
	// 정적변수
	Vector2 mPos;
	eDirection mDir;

	Node* mHead;
	eGameObjectType mType;
};