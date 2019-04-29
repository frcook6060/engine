#pragma once


enum InputState
{
	IS_RELEASE = 0,
	IS_DOWN,
	IS_PRESS,
	IS_UP
};

enum Keyboard
{
	KB_UNKNOWN			= 0x00,
	KB_CANCEL			= 0x03,
	KB_BACKSPACE		= 0x08,
	KB_TAB				= 0x09,
	KB_CLEAR			= 0x0C,
	KB_RETURN			= 0x0D,
	KB_SHIFT			= 0x10,
	KB_CONTROL			= 0x11,
	KB_MENU				= 0x12,
	KB_PAUSE			= 0x13,
	KB_CAPITAL			= 0x14,
	KB_ESCAPE			= 0x1B,
	KB_CONVERT			= 0x1C,
	KB_NONCONVERT		= 0x1D,
	KB_ACCEPT			= 0x1E,
	KB_MODECHANGE		= 0x1F,
	KB_SPACE			= 0x20,
	KB_PRIOR			= 0x21,
	KB_NEXT				= 0x22,
	KB_END				= 0x23,
	KB_HOME				= 0x24,
	KB_LEFT				= 0x25,
	KB_UP				= 0x26,
	KB_RIGHT			= 0x27,
	KB_DOWN				= 0x28,
	KB_SELECT			= 0x29,
	KB_PRINT			= 0x2A,
	KB_EXECUTE			= 0x2B,
	KB_SNAPSHOT			= 0x2C,
	KB_INSERT			= 0x2D,
	KB_DELETE			= 0x2E,
	KB_HELP				= 0x2F,
	KB_0				= 0x30,
	KB_1				= 0x31,
	KB_2				= 0x32,
	KB_3				= 0x33,
	KB_4				= 0x34,
	KB_5				= 0x35,
	KB_6				= 0x36,
	KB_7				= 0x37,
	KB_8				= 0x38,
	KB_9				= 0x39,
	KB_A				= 0x41,
	KB_B				= 0x42,
	KB_C				= 0x43,
	KB_D				= 0x44,
	KB_E				= 0x45,
	KB_F				= 0x46,
	KB_G				= 0x47,
	KB_H				= 0x48,
	KB_I				= 0x49,
	KB_J				= 0x4A,
	KB_K				= 0x4B,
	KB_L				= 0x4C,
	KB_M				= 0x4D,
	KB_N				= 0x4E,
	KB_O				= 0x4F,
	KB_P				= 0x50,
	KB_Q				= 0x51,
	KB_R				= 0x52,
	KB_S				= 0x53,
	KB_T				= 0x54,
	KB_U				= 0x55,
	KB_V				= 0x56,
	KB_W				= 0x57,
	KB_X				= 0x58,
	KB_Y				= 0x59,
	KB_Z				= 0x5A,
	KB_LWIN				= 0x5B,
	KB_RWIN				= 0x5C,
	KB_APPS				= 0x5D,
	KB_SLEEP			= 0x5F,
	KB_NUMPAD_0			= 0x60,
	KB_NUMPAD_1			= 0x61,
	KB_NUMPAD_2			= 0x62,
	KB_NUMPAD_3			= 0x63,
	KB_NUMPAD_4			= 0x64,
	KB_NUMPAD_5			= 0x65,
	KB_NUMPAD_6			= 0x66,
	KB_NUMPAD_7			= 0x67,
	KB_NUMPAD_8			= 0x68,
	KB_NUMPAD_9			= 0x69,
	KB_MULTIPLY			= 0x6A,
	KB_ADD				= 0x6B,
	KB_SEPARATOR		= 0x6C,
	KB_SUBTRACT			= 0x6D,
	KB_DECIMAL			= 0x6E,
	KB_DIVIDE			= 0x6F,
	KB_F1				= 0x70,
	KB_F2				= 0x71,
	KB_F3				= 0x72,
	KB_F4				= 0x73,
	KB_F5				= 0x74,
	KB_F6				= 0x75,
	KB_F7				= 0x76,
	KB_F8				= 0x77,
	KB_F9				= 0x78,
	KB_F10				= 0x79,
	KB_F11				= 0x7A,
	KB_F12				= 0x7B,
	KB_F13				= 0x7C,
	KB_F14				= 0x7D,
	KB_F15				= 0x7E,
	KB_F16				= 0x7F,
	KB_F17				= 0x80,
	KB_F18				= 0x81,
	KB_F19				= 0x82,
	KB_F20				= 0x83,
	KB_F21				= 0x84,
	KB_F22				= 0x85,
	KB_F23				= 0x86,
	KB_F24				= 0x87,
	KB_NUMLOCK			= 0x90,
	KB_SCROLL			= 0x91,
	KB_LSHIFT			= 0xA0,
	KB_RSHIFT			= 0xA1,
	KB_LCONTROL			= 0xA2,
	KB_RCONTROL			= 0xA3,
	KB_LMENU			= 0xA4,
	KB_RMENU			= 0xA5,
	KB_BROWSER_BACK		= 0xA6,
	KB_BROWSER_FORWORD	= 0xA7,
	KB_BROWSER_REFRESH	= 0xA8,
	KB_BROWSER_STOP		= 0xA9,
	KB_BROWSER_SEARCH	= 0xAA,
	KB_BROWSER_FAVORITES = 0xAB,
	KB_BROWSER_HOME		= 0xAC,
	KB_VOLUMN_MUTE		= 0xAD,
	KB_VOLUMN_DOWN		= 0xAE,
	KB_VOLUMN_UP		= 0xAF,
	KB_MEDIA_NEXT_TRACK	= 0xB0,
	KB_MEDIA_PREV_TRACK = 0xB1,
	KB_MEDIA_STOP		= 0xB2,
	KB_MEDIA_PAUSE		= 0xB3,
	KB_LAUNCH_MAIL		= 0xB4,
	KB_LAUNCH_MEDIA_SELECT = 0xB5,
	KB_LAUNCH_APP1		= 0xB6,
	KB_LAUNCH_APP2		= 0xB7,
	KB_OEM_1			= 0xBA,
	KB_OEM_PLUS			= 0xBB,
	KB_OEM_COMMA		= 0xBC,
	KB_OEM_MINUS		= 0xBD,
	KB_OEM_PERIOD		= 0xBE,
	KB_OEM_2			= 0xBF,
	KB_OEM_3			= 0xC0,
	KB_OEM_4			= 0xDB,
	KB_OEM_5			= 0xDC,
	KB_OEM_6			= 0xDD,
	KB_OEM_7			= 0xDE,
	KB_OEM_8			= 0xDF,
	KB_OEM_102			= 0xE2,
	KB_PROCESSKEY		= 0xE5,
	KB_PACKET			= 0xE7,
	KB_ATTN				= 0xF6,
	KB_CRSEL			= 0xF7,
	KB_EXSEL			= 0xF8,
	KB_EREOF			= 0xF9,
	KB_PLAY				= 0xFA,
	KB_ZOOM				= 0xFB,
	KB_NONAME			= 0xFC,
	KB_PA1				= 0xFD,
	KB_OEM_CLEAR		= 0xFE
};

enum MouseButton
{
	MB_UNKNOWN			= 0x00,
	MB_LBUTTON			= 0x01,
	MB_RBUTTON			= 0x02,
	MB_MBUTTON			= 0x04,
};

#define INPUT_SIZE		  0xFF

void input_init();

void input_event(UINT message, WPARAM wparam, LPARAM lparam);

void input_update();

void input_release();

// keyboard
bool input_isKeyRelease(Keyboard key);
bool input_isKeyDown(Keyboard key);
bool input_isKeyPress(Keyboard key);
bool input_isKeyUp(Keyboard key);

// mouse button
bool input_isMouseRelease(MouseButton mb);
bool input_isMouseDown(MouseButton mb);
bool input_isMousePress(MouseButton mb);
bool input_isMouseUp(MouseButton mb);

POINT input_getCursor();

bool input_isGrab();
void input_setGrab(bool grab);

void input_toggle();