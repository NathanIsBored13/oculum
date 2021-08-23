#include "ocpch.h"
#include "Window.h"

#include "Events/MouseEvents.h"
#include "WindowManager.h"

namespace Oculum
{
	Window::WindowTemplate Window::WindowTemplate::wndClass;

	Window::WindowTemplate::WindowTemplate() noexcept : hInst(GetModuleHandle(nullptr))
	{
		WNDCLASSEX wnd =
		{
			sizeof(wnd),
			CS_OWNDC,
			HandleMsgSetup,
			0,
			0,
			GetInstance(),
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			GetName(),
			nullptr
		};
		RegisterClassEx(&wnd);
	}

	Window::WindowTemplate::~WindowTemplate()
	{
		UnregisterClass(wndClassName, GetInstance());
	}

	const wchar_t* Window::WindowTemplate::GetName() noexcept
	{
		return wndClassName;
	}

	HINSTANCE Window::WindowTemplate::GetInstance() noexcept
	{
		return wndClass.hInst;
	}

	Window::Window(const wchar_t* name, int width, int height, Window* parent, WindowManager* windowManager) : width(width), height(height), name(name), parent(parent), windowManager(windowManager)
	{
		if (parent != nullptr)
		{
			parent->AddChild(this);
		}
		RECT wr
		{
			100,
			100,
			width + 100,
			height + 100
		};
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
		hWnd = CreateWindowEx(0, WindowTemplate::GetName(), name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, parent == nullptr ? nullptr : parent->GetHwnd(), nullptr, WindowTemplate::GetInstance(), this);
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		stack = LayerStack();
		windowManager->RegisterWindow(this);
	}

	Window::~Window()
	{

	}

	void Window::OnUpdate(float fElapsed)
	{
		stack.OnUpdate(fElapsed);
		OnUpdateClient(fElapsed);
	}

	void Window::AddChild(Window* child)
	{
		children.push_back(child);
	}

	void Window::RemoveChild(Window* child)
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			if (children[i] == child)
			{
				children.erase(children.begin() + i);
			}
		}
	}

	void Window::CloseWindow(int exitCode)
	{
		if (parent != nullptr && exitCode != Window::ExitCode::Closed_Due_To_Parent)
		{
			parent->RemoveChild(this);
		}
		for (Window* wnd : children)
		{
			wnd->CloseWindow(Window::ExitCode::Closed_Due_To_Parent);
		}
		this->exitCode = exitCode;
		DestroyWindow(hWnd);
	}

	WindowManager* Window::GetWindowManager()
	{
		return windowManager;
	}

	LayerStack* Window::GetStack()
	{
		return &stack;
	}

	HWND Window::GetHwnd()
	{
		return hWnd;
	}

	LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)  noexcept
	{
		LRESULT ret;
		if (msg == WM_NCCREATE)
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
			ret = pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}
		else
		{
			ret = DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return ret;
	}

	LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)  noexcept
	{
		return reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA))->HandleMsg(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (msg)
		{
		case WM_CLOSE:
			if (OnClose())
			{
				CloseWindow(0);
			}
			return 0;
			break;
		case WM_DESTROY:
			PostMessage(nullptr, WM_QUIT, exitCode, reinterpret_cast<LPARAM>(this));
			break;
		case WM_MOUSEMOVE:
			stack.OnEvent(new MouseMovedEvent(0, (int)LOWORD(lParam), (int)HIWORD(lParam)));
			break;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}