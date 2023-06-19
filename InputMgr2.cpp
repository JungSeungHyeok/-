#include "InputMgr2.h"
#include <iostream>
#include <algorithm>

vector<bool> InputMgr2::downList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::ingList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::upList(Keyboard::Key::KeyCount);

void InputMgr2::Clear()
{
    // clear�� ��� ��� ���� �� ���� �۾� ����
    // for�� ������ ��� �佺�� false�� ä��

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
    case Event::KeyPressed: // �������� ����
        // ingList�� �������� Ʈ��
        if (!ingList[ev.key.code])
        {
            downList[ev.key.code] = true;
            ingList[ev.key.code] = true;
        }
        break;
    case Event::KeyReleased: // Ű�� ��������
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
    if (key >= 0 && key < Keyboard::KeyCount) // ��ȿ�� ���� Ȯ��
    {   // ingList ������ �ε��� �������� �ִ���
        // Ȯ���� ������ key���� ��ȯ
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
