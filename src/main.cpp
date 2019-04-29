#include "sys.h"


class AppTest : public IApp
{
public:
	virtual void init() 
	{
	}

	virtual void update()
	{
		if (input_isKeyDown(KB_ESCAPE))
		{
			app_quit();
		}

		if (input_isKeyDown(KB_TAB))
		{
			input_toggle();
		}

		if (input_isGrab())
		{
			std::stringstream ss;
			POINT p = input_getCursor();

			ss << p.x << ", " << p.y << std::endl;

			OutputDebugString(ss.str().c_str());
		}
	}

	virtual void fixedUpdate()
	{
	}

	virtual void render()
	{
	}

	virtual void release()
	{
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