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

int SetWindowTitle(lua_State* pLuaState)
{
	GarrysMod::Lua::ILuaBase* pLua = pLuaState->luabase;

	if (!GetMainWindow())
	{
		pLua->ThrowError("Can't find main process window!");
		return 0;
	}

	const char* pszWindowTitle = pLua->CheckString(1);
	SetWindowTextA(hMainWindow, pszWindowTitle);

	return 0;
}

int GetWindowTitle(lua_State* pLuaState)
{
	GarrysMod::Lua::ILuaBase* pLua = pLuaState->luabase;

	if (!GetMainWindow())
	{
		pLua->ThrowError("Can't find main process window!");
		return 0;
	}

	char Buffer[256];
	int Length = GetWindowTextA(hMainWindow, Buffer, sizeof(Buffer));

	if (Length <= 0)
	{
		pLua->PushString("");
		return 1;
	}

	pLua->PushString(Buffer);
	return 1;
}

GMOD_MODULE_OPEN()
{
	GarrysMod::Lua::ILuaBase* pLua = LUA;

	pLua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		pLua->PushString("SetWindowTitle");
		pLua->PushCFunction(SetWindowTitle);
		pLua->RawSet(-3);

		pLua->PushString("GetWindowTitle");
		pLua->PushCFunction(GetWindowTitle);
		pLua->RawSet(-3);
	}
	pLua->Pop();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	GarrysMod::Lua::ILuaBase* pLua = LUA;

	pLua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		pLua->PushString("SetWindowTitle");
		pLua->PushNil();
		pLua->RawSet(-3);

		pLua->PushString("GetWindowTitle");
		pLua->PushNil();
		pLua->RawSet(-3);
	}
	pLua->Pop();

	return 0;
}