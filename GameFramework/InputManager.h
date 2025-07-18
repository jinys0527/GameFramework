#pragma once
#include "SingletonBase.h"
#include <unordered_set>

class InputManager : public SingletonBase<InputManager>
{
public:
	void Update();
	void OnKeyDown(char key);
	void OnKeyUp(char key);
	bool IsKeyPressed(char key) const;

private:
	std::unordered_set<char> keysDown;			// ���� ����
	std::unordered_set<char> keysDownPrev;		// ���� ������ ����
};

