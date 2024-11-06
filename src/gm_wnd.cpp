#define WIN32_LEAN_AND_MEAN

#include <GarrysMod/Lua/Interface.h>
#include <Windows.h>

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

LUA_FUNCTION(SetWindowTitle)
{
	if (!GetMainWindow())
	{
		LUA->ThrowError("Can't find main process window!");
		return 0;
	}

	const char* pszWindowTitle = LUA->CheckString(1);
	SetWindowTextA(hMainWindow, pszWindowTitle);

	return 0;
}

LUA_FUNCTION(GetWindowTitle)
{
	if (!GetMainWindow())
	{
		LUA->ThrowError("Can't find main process window!");
		return 0;
	}

	char Buffer[256];
	int Length = GetWindowTextA(hMainWindow, Buffer, sizeof(Buffer));

	if (Length <= 0)
	{
		LUA->PushString("");
		return 1;
	}

	LUA->PushString(Buffer);
	return 1;
}

GMOD_MODULE_OPEN()
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("SetWindowTitle");
		LUA->PushCFunction(SetWindowTitle);
		LUA->RawSet(-3);

		LUA->PushString("GetWindowTitle");
		LUA->PushCFunction(GetWindowTitle);
		LUA->RawSet(-3);
	}
	LUA->Pop();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("SetWindowTitle");
		LUA->PushNil();
		LUA->RawSet(-3);

		LUA->PushString("GetWindowTitle");
		LUA->PushNil();
		LUA->RawSet(-3);
	}
	LUA->Pop();

	return 0;
}