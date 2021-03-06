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

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = g_config->width;
	rect.bottom = g_config->height;

	AdjustWindowRectEx(
		&rect,
		WIN_WS_TYPE,
		FALSE,
		WS_EX_CLIENTEDGE);

	std::stringstream ss;
	ss << rect.left << ", " << rect.right << ", " << rect.top << ", " << rect.bottom << std::endl;

	OutputDebugString(ss.str().c_str());

	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	ss.str("");

	ss << windowWidth << ", " << windowHeight << std::endl;
	OutputDebugString(ss.str().c_str());

	g_config->hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_config->winClass.c_str(),
		g_config->caption.c_str(),
		WIN_WS_TYPE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
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

	input_init();

	rend_init();

	// Handle Timer
	QueryPerformanceFrequency(&g_config->timer.clockFreq);


	if (g_config->app)
	{
		g_config->app->init();
	}
}

void app_update()
{

	QueryPerformanceCounter(&g_config->timer.startTime);

	while (g_config->isRunning)
	{
		QueryPerformanceCounter(&g_config->timer.endTimer);
		
		LARGE_INTEGER delta;

		delta.QuadPart = g_config->timer.endTimer.QuadPart - g_config->timer.startTime.QuadPart;

		g_config->timer.delta = ((float)delta.QuadPart) / ((float)g_config->timer.clockFreq.QuadPart);

		g_config->timer.startTime.QuadPart = g_config->timer.endTimer.QuadPart;

		g_config->timer.fixedDelta += g_config->timer.delta;

		while (PeekMessage(&g_config->msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&g_config->msg);
			DispatchMessage(&g_config->msg);
		}


		if (g_config->app)
		{
			g_config->app->update();

			if (g_config->timer.fixedDelta >= G_TIME)
			{
				g_config->app->fixedUpdate();
			}

			g_config->app->render();
		}


		if (g_config->timer.fixedDelta >= G_TIME)
		{
			g_config->timer.fixedDelta = 0.0f;
		}

		input_update();
	}
}

WPARAM app_release()
{
	if (g_config->app)
	{
		g_config->app->release();
	}

	rend_release();

	input_release();

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
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
		input_event(msg, wparam, lparam);
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
