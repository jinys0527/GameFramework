#include "pch.h"
#include "MainApp.h"
#include "TestListener.h"

TestListener* test;

bool MainApp::Initialize()
{
	const wchar_t* className = L"GameFramework";
	const wchar_t* windowName = L"GameFramework";

	if (false == Create(className, windowName, 1024, 800))
	{
		return false;
	}
	m_EventDispatcher = std::make_unique<EventDispatcher>();
	m_InputManager = std::make_unique<InputManager>(*m_EventDispatcher);
	m_Renderer = std::make_unique<D2DRenderer>();
	m_AssetManager = std::make_unique<AssetManager>(*m_Renderer);

	m_Renderer->Initialize(m_hwnd);

	m_GameTimer.Reset();

	test = new TestListener();
	m_EventDispatcher->AddListener(EventType::KeyDown, test);
	m_EventDispatcher->AddListener(EventType::KeyUp, test);

	return true;
}

void MainApp::Run()
{
	MSG msg = { 0 };

	m_testBitmap = m_AssetManager->LoadTexture(L"cat_texture", L"../Resource/cat.png");
	assert(m_testBitmap != nullptr && "Failed to load test bitmap.");

	m_background = m_AssetManager->LoadTexture(L"vecteezy", L"../Resource/vecteezy.png");
	assert(m_background != nullptr && "Failed to load background texture.");

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if(false == m_InputManager->OnHandleMessage(msg))
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
	delete test;
	__super::Destroy();

}

bool MainApp::OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return false;
}

void MainApp::UpdateTime()
{
	m_GameTimer.Tick();
}

void MainApp::UpdateInput()
{
}

void MainApp::UpdateLogic()
{
	m_InputManager->Update();
}

void MainApp::Render()
{
	if (m_Renderer == nullptr) return;

	D2D1_SIZE_F srcSize = m_testBitmap->GetSize();
	D2D1_RECT_F srcRect = D2D1::RectF(0.0f, 0.0f, srcSize.width, srcSize.height);

	m_Renderer->SetTarget();

	m_Renderer->GetD2DContext()->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

	m_Renderer->RenderBegin();

	m_Renderer->SetTransform(D2D1::Matrix3x2F::Identity());

	//배경 그리기
	if (m_background != nullptr)
	{
		D2D1_SIZE_F bgSize = m_background->GetSize();
		D2D1_RECT_F bgRect = D2D1::RectF(0.f, 0.f, bgSize.width * 2, bgSize.height * 2);

		m_Renderer->DrawBitmap(m_background.Get(), bgRect);
	}

	// 원본 그리기
	m_Renderer->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 400.f));

	m_Renderer->DrawBitmap(m_testBitmap.Get(), srcRect);

	m_Renderer->RenderEnd();
}

void MainApp::OnResize(int width, int height)
{
	__super::OnResize(width, height);
}

void MainApp::OnClose()
{
}
