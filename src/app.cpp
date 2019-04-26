#include "sys.h"


static AppConfig* g_config = nullptr;

static LRESULT CALLBACK _wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void app_init(AppConfig* config)
{
	g_config = config;

	ZeroMemory(&g_config->wc, sizeof(g_config->wc));

	g_config->wc.cbSize = sizeof(g_config->wc);
	g_config->wc.lpfnWndProc = _wndProc;
	g_config->wc.hInstance = g_config->hinstance;
	g_config->wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	g_config->wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	g_config->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	g_config->wc.lpszClassName = g_config->winClass.c_str();
	g_config->wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (!RegisterClassEx(&g_config->wc))
	{
		MessageBox(nullptr, "Window Registers Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		app_quit();
		return;
	}


	g_config->hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_config->winClass.c_str(),
		g_config->caption.c_str(),
		WIN_WS_TYPE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		g_config->width,
		g_config->height,
		nullptr,
		nullptr,
		g_config->hinstance,
		nullptr
	);

	if (g_config->hwnd == nullptr)
	{
		MessageBox(nullptr, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		app_quit();
		return;
	}

	ShowWindow(g_config->hwnd, g_config->cmdShow);
	UpdateWindow(g_config->hwnd);


	if (g_config->app)
	{
		g_config->app->init();
	}
}

void app_update()
{

	while (g_config->isRunning)
	{
		while (PeekMessage(&g_config->msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&g_config->msg);
			DispatchMessage(&g_config->msg);
		}


		if (g_config->app)
		{
			g_config->app->update(1.0f);
			g_config->app->fixedUpdate();
			g_config->app->render();
		}
	}
}

WPARAM app_release()
{
	if (g_config->app)
	{
		g_config->app->release();
	}

	return g_config->msg.wParam;
}

AppConfig* app_getConfig()
{
	return g_config;
}

static LRESULT CALLBACK _wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		app_quit();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}

void app_quit()
{
	g_config->isRunning = false;
}
