#pragma once


#define WIN_WS_TYPE WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX


class IApp
{
public:

	virtual void init() = 0;

	virtual void update(float delta) = 0;

	virtual void fixedUpdate() = 0;

	virtual void render() = 0;

	virtual void release() = 0;
};


struct AppConfig
{
	HINSTANCE hinstance;
	int cmdShow;
	std::string winClass = "_engine_window"; 
	std::string caption = "Engine Window";
	uint32_t width = 1280; // Default 1280x720
	uint32_t height = 720;
	IApp* app = nullptr; // Default to Nullptr

	// Stuff you don't need to set...
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	bool isRunning = true; // Default to true
};

void app_init(AppConfig* config);

void app_update();

WPARAM app_release();

AppConfig* app_getConfig();

void app_quit();
