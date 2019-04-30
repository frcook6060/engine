#include "sys.h"


class AppTest : public IApp
{
private:

public:
	virtual void init() 
	{
	}

	virtual void update()
	{
	}

	virtual void fixedUpdate()
	{
	}

	virtual void render()
	{
		rend_clear(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 1.0f);
		// Render something here...

		rend_present();
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