#include "InputMgr2.h"
#include <iostream>
#include <algorithm>

vector<bool> InputMgr2::downList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::ingList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::upList(Keyboard::Key::KeyCount);

void InputMgr2::Clear()
{
    // clear는 모든 요소 제거 후 비우는 작업 실행
    // for문 벡터의 모든 요스를 false로 채움

    for (int i = 0; i < Keyboard::Key::KeyCount; i++)
    {
        downList[i] = false;
        upList[i] = false;
    }
}

void InputMgr2::Update(Event& ev)
{
    switch (ev.type)
    {
    case Event::KeyPressed: // 눌렀을때 실행
        // ingList는 눌렀을때 트루
        if (!ingList[ev.key.code])
        {
            downList[ev.key.code] = true;
            ingList[ev.key.code] = true;
        }
        break;
    case Event::KeyReleased: // 키가 눌린상태
        ingList[ev.key.code] = false;
        upList[ev.key.code] = true;
        break;
    }
}

bool InputMgr2::GetKeyDown(Keyboard::Key key)
{
    if (key >= 0 && key < Keyboard::KeyCount)
        return downList[key];
    return false;
}

bool InputMgr2::GetKey(Keyboard::Key key)
{
    if (key >= 0 && key < Keyboard::KeyCount) // 유효한 범위 확인
    {   // ingList 벡터의 인덱스 범위내에 있는지
        // 확인후 유요한 key값을 반환
        return ingList[key];
    }    
    return false;
}

bool InputMgr2::GetKeyUp(Keyboard::Key key)
{
    if (key >= 0 && key < Keyboard::KeyCount)
    {
        return upList[key];
    }
    return false;
}
