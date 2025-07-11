#include "pch.h"
#include "MainApp.h"

bool MainApp::Initialize()
{
	const wchar_t* className = L"GameFramework";
	const wchar_t* windowName = L"GameFramework";

	if (false == Create(className, windowName, 1024, 800))
	{
		return false;
	}
	
	m_GameTimer.Reset();

	return true;
}

void MainApp::Run()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			UpdateTime();
			UpdateInput();
			UpdateLogic();
			Render();
		}
	}
}

void MainApp::Finalize()
{

}

bool MainApp::OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return false;
}

void MainApp::UpdateTime()
{
	m_GameTimer.Tick();
	std::cout << m_GameTimer.TotalTime() << std::endl;
}

void MainApp::UpdateInput()
{
}

void MainApp::UpdateLogic()
{
}

void MainApp::Render()
{
}

void MainApp::OnResize(int width, int height)
{
	__super::OnResize(width, height);
}

void MainApp::OnClose()
{
}
