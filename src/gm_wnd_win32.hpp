#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

namespace gmWnd
{
	HWND hMainWindow;

	BOOL CALLBACK EnumWindowsProc(HWND hWindow, LPARAM lpReserved)
	{
		DWORD dwProcessID;
		GetWindowThreadProcessId(hWindow, &dwProcessID);

		if (dwProcessID != GetCurrentProcessId()) return true;
		if (GetWindow(hWindow, GW_OWNER) != NULL) return true;
		if (!IsWindowVisible(hWindow)) return true;

		hMainWindow = hWindow;
		return false;
	}

	bool GetMainWindow()
	{
		if (IsWindow(hMainWindow)) return true;

		EnumWindows(EnumWindowsProc, 0);

		return IsWindow(hMainWindow);
	}

	const char* GetWindowTitle()
	{
		char Buffer[256];
		int Length = GetWindowTextA(hMainWindow, Buffer, sizeof(Buffer));

		if (Length <= 0) return "";

		return Buffer;
	}

	void SetWindowTitle(const char* pszWindowTitle)
	{
		if (!GetMainWindow()) return;

		SetWindowTextA(hMainWindow, pszWindowTitle);
	}
};