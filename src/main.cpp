#include <iostream>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(nullptr, "Goodbye, cruel world!", "Note", MB_OK);
	return 0;
}