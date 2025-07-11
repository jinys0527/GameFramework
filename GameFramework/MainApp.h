#pragma once

#include "NzWndBase.h"
#include "GameTimer.h"

#include <wrl/client.h>



class MainApp : public NzWndBase
{
public:
	MainApp() = default;
	virtual ~MainApp() = default;

	bool Initialize();
	void Run();
	void Finalize();

	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;

private:
	void UpdateTime();
	void UpdateInput();
	void UpdateLogic();

	void Render();
	
	void OnResize(int width, int height) override;
	void OnClose() override;

	GameTimer m_GameTimer;
};

