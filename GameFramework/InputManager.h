#pragma once
#include <unordered_set>

class InputManager
{
public:
	void Update();
	void OnKeyDown(char key);
	void OnKeyUp(char key);
	bool IsKeyPressed(char key) const;

private:
	std::unordered_set<char> keysDown;			// 현재 눌림
	std::unordered_set<char> keysDownPrev;		// 이전 프레임 눌림
};

