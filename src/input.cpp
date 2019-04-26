#include "sys.h"


void onKeyDown(UINT message, WPARAM wparam, LPARAM lparam);

void onKeyUp(UINT message, WPARAM wparam, LPARAM lparam);

void input_init()
{

}

void input_event(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		onKeyDown(message, wparam, lparam);
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		onKeyUp(message, wparam, lparam);
		break;
	}
}

void input_update()
{
}

void onKeyDown(UINT msg, WPARAM wparam, LPARAM lparam)
{
}

void onKeyUp(UINT msg, WPARAM wparam, LPARAM lparam)
{
}
