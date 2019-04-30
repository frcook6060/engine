#include "app_test.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow)
{
	AppTest test;
	AppConfig config;

	config.hinstance = hInst;
	config.cmdShow = nCmdShow;
	config.app = &test;

	app_init(&config);

	app_update();

	return app_release();

}