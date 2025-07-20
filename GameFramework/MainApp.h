#pragma once

#include "NzWndBase.h"
#include "GameTimer.h"

#include <wrl/client.h>
#include "InputManager.h"
#include "EventDispatcher.h"
#include "AssetManager.h"
#include <memory>


class MainApp : public NzWndBase
{
public:
	MainApp() : NzWndBase(), m_InputManager(std::make_unique<InputManager>()), m_AssetManager(std::make_unique<AssetManager>()), m_EventDispatcher(std::make_unique<EventDispatcher>()) {}
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
	std::unique_ptr<InputManager> m_InputManager;
	std::unique_ptr<AssetManager> m_AssetManager;
	std::unique_ptr<EventDispatcher> m_EventDispatcher;
};

