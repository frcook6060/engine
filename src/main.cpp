#include "sys.h"


class AppTest : public IApp
{
private:
	int i = 0;

	std::ofstream out;

public:
	virtual void init() 
	{
		out.open("debug.txt");
	}

	virtual void update()
	{
	}

	virtual void fixedUpdate()
	{
	}

	virtual void render()
	{
	}

	virtual void release()
	{
		out.close();
	}
};

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