#ifdef _WIN32
#include "gm_wnd_win32.hpp"
#else
#include "gm_wnd_linux.hpp"
#endif

#include <GarrysMod/Lua/Interface.h>

LUA_FUNCTION(SetWindowTitle)
{
	if (!gmWnd::GetMainWindow())
	{
		LUA->ThrowError("Can't find main process window!");
		return 0;
	}

	gmWnd::SetWindowTitle(LUA->CheckString(1));

	return 0;
}

LUA_FUNCTION(GetWindowTitle)
{
	if (!gmWnd::GetMainWindow())
	{
		LUA->ThrowError("Can't find main process window!");
		return 0;
	}
	
	LUA->PushString(gmWnd::GetWindowTitle());
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