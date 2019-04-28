#include "sys.h"



static std::vector<InputState> inputStates;
static POINT cursor;

void onInputDown(UINT message, WPARAM wparam, LPARAM lparam);

void onInputUp(UINT message, WPARAM wparam, LPARAM lparam);

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
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		onInputDown(message, wparam, lparam);
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		onInputUp(message, wparam, lparam);
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
}

void onInputDown(UINT msg, WPARAM wparam, LPARAM lparam)
{
	std::stringstream ss;
	ss << "down: " << wparam << std::endl;
	OutputDebugString(ss.str().c_str());

	if (inputStates[wparam] == IS_RELEASE)
	{
		inputStates[wparam] = IS_DOWN;
	}
}

void onInputUp(UINT msg, WPARAM wparam, LPARAM lparam)
{
	std::stringstream ss;
	ss << "up: " << wparam << std::endl;
	OutputDebugString(ss.str().c_str());

	if (inputStates[wparam] == IS_PRESS)
	{
		inputStates[wparam] = IS_UP;
	}
}

void onMouseMove(UINT message, WPARAM wparam, LPARAM lparam)
{
	cursor.x = LOWORD(lparam);
	cursor.y = HIWORD(lparam);
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