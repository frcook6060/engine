#include "sys.h"



static std::vector<InputState> inputStates;
static POINT pre;
static POINT cursor;

static bool capture = false;

void onInputDown(UINT message, WPARAM wparam, LPARAM lparam);

void onInputUp(UINT message, WPARAM wparam, LPARAM lparam);

void onMouseDown(UINT message, WPARAM wparam, LPARAM lparam);

void onMouseUp(UINT message, WPARAM wparam, LPARAM lparam);

void onMouseMove(UINT message, WPARAM wparam, LPARAM lparam);

void input_init()
{
	inputStates.resize(INPUT_SIZE);

	std::for_each(
		inputStates.begin(), 
		inputStates.end(), 
		[&](InputState& state) {
			state = IS_RELEASE;
		});
}

void input_event(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		onInputDown(message, wparam, lparam);
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		onInputUp(message, wparam, lparam);
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		onMouseDown(message, wparam, lparam);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		onMouseUp(message, wparam, lparam);
		break;
	case WM_MOUSEMOVE:
		onMouseMove(message, wparam, lparam);
		break;
	}
}

void input_update()
{
	std::for_each(
		inputStates.begin(),
		inputStates.end(),
		[&](InputState& state) {
			if (state == IS_DOWN)
			{
				state = IS_PRESS;
			}

			if (state == IS_UP)
			{
				state = IS_RELEASE;
			}
		}
	);

	if (capture)
	{
		cursor.x = 0;
		cursor.y = 0;
	}
}

void input_release()
{
	ReleaseCapture();
}

void onInputDown(UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (inputStates[wparam] == IS_RELEASE)
	{
		inputStates[wparam] = IS_DOWN;
	}
}

void onInputUp(UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (inputStates[wparam] == IS_PRESS)
	{
		inputStates[wparam] = IS_UP;
	}
}

void onMouseDown(UINT message, WPARAM wparam, LPARAM lparam)
{
	MouseButton button = MB_UNKNOWN;

	if (message == WM_LBUTTONDOWN)
	{
		button = MB_LBUTTON;
	}
	else if (message == WM_RBUTTONDOWN)
	{
		button = MB_RBUTTON;
	}
	else if (message == WM_MBUTTONDOWN)
	{
		button = MB_MBUTTON;
	}
	else
	{
		return;
	}

	if (inputStates[button] == IS_RELEASE)
	{
		inputStates[button] = IS_DOWN;
	}
}

void onMouseUp(UINT message, WPARAM wparam, LPARAM lparam)
{
	MouseButton button = MB_UNKNOWN;

	if (message == WM_LBUTTONUP)
	{
		button = MB_LBUTTON;
	}
	else if (message == WM_RBUTTONUP)
	{
		button = MB_RBUTTON;
	}
	else if (message == WM_MBUTTONUP)
	{
		button = MB_MBUTTON;
	}
	else
	{
		return;
	}

	if (inputStates[button] == IS_PRESS)
	{
		inputStates[button] = IS_UP;
	}
}

void onMouseMove(UINT message, WPARAM wparam, LPARAM lparam)
{
	if (capture)
	{
		int mx = LOWORD(lparam);
		int my = HIWORD(lparam);

		if (mx <= 0)
		{
			mx += (app_getConfig()->width / 2);
			pre.x += (app_getConfig()->width / 2);
			SetCursorPos(mx, my);
		}
		else if (mx >= app_getConfig()->width - 1)
		{
			mx -= (app_getConfig()->width / 2);
			pre.x -= (app_getConfig()->width / 2);
			SetCursorPos(mx, my);
		}

		if (my <= 0)
		{
			my += (app_getConfig()->height / 2);
			pre.y += (app_getConfig()->height / 2);
			SetCursorPos(mx, my);
		}
		else if (my >= app_getConfig()->height - 1)
		{
			my -= (app_getConfig()->height / 2);
			pre.y -= (app_getConfig()->height / 2);
			SetCursorPos(mx, my);
		}

		cursor.x = mx - pre.x;
		cursor.y = my - pre.y;

		pre.x = mx;
		pre.y = my;

	}
	else
	{
		cursor.x = LOWORD(lparam);
		cursor.y = HIWORD(lparam);
	}
}

bool input_isKeyRelease(Keyboard key)
{
	return inputStates[key] == IS_RELEASE;
}

bool input_isKeyDown(Keyboard key)
{
	return inputStates[key] == IS_DOWN;
}

bool input_isKeyPress(Keyboard key)
{
	return inputStates[key] == IS_PRESS;
}

bool input_isKeyUp(Keyboard key)
{
	return inputStates[key] == IS_UP;
}

// mouse button
bool input_isMouseRelease(MouseButton mb)
{
	return inputStates[mb] == IS_RELEASE;
}

bool input_isMouseDown(MouseButton mb)
{
	return inputStates[mb] == IS_DOWN;
}

bool input_isMousePress(MouseButton mb)
{
	return inputStates[mb] == IS_PRESS;
}

bool input_isMouseUp(MouseButton mb)
{
	return inputStates[mb] == IS_UP;
}

POINT input_getCursor()
{
	return cursor;
}

bool input_isGrab()
{
	return capture;
}

void input_setGrab(bool grab)
{
	capture = grab;
	if (capture)
	{
		ShowCursor(FALSE);
		//SetCapture(app_getConfig()->hwnd);
		RECT rect;
		GetClientRect(app_getConfig()->hwnd, &rect);
		ClientToScreen(app_getConfig()->hwnd, reinterpret_cast<POINT*>(&rect.left));
		ClientToScreen(app_getConfig()->hwnd, reinterpret_cast<POINT*>(&rect.right));

		//ClientToScreen(app_getConfig()->hwnd, &rect);
		ClipCursor(&rect);

		SetCursorPos(app_getConfig()->width / 2, app_getConfig()->height / 2);

		pre.x = cursor.x = app_getConfig()->width / 2;
		pre.y = cursor.y = app_getConfig()->height / 2;
	}
	else
	{
		ShowCursor(TRUE);
		ClipCursor(nullptr);
	}
}

void input_toggle()
{
	input_setGrab(!input_isGrab());
}