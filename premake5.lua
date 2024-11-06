PROJECT_GENERATOR_VERSION = 3

filter("platforms:x86")
	include("./garrysmod_common_x86")

	CreateWorkspace({name = "wnd86", abi_compatible = false, path = "./projects/"})
		CreateProject({serverside = false, source_path = "./src", manual_files = false})
			cppdialect("c++20")
			architecture("x86")

			-- IncludeHelpersExtended()
			IncludeLuaShared()
			IncludeDetouring()
			-- IncludeScanning()
			IncludeSDKCommon()
			IncludeSDKTier0()
			IncludeSDKTier1()
			-- IncludeSDKTier2()
			-- IncludeSDKTier3()
			-- IncludeSDKMathlib()
			-- IncludeSDKRaytrace()
			-- IncludeSteamAPI()

			files({
				"./src/**.*"
			})

filter("platforms:x64")
	include("./garrysmod_common_x64")

	CreateWorkspace({name = "wnd64", abi_compatible = false, path = "./projects/"})
		CreateProject({serverside = false, source_path = "./src", manual_files = false})
			cppdialect("c++20")
			architecture("x64")

			-- IncludeHelpersExtended()
			IncludeLuaShared()
			IncludeDetouring()
			-- IncludeScanning()
			IncludeSDKCommon()
			IncludeSDKTier0()
			IncludeSDKTier1()
			-- IncludeSDKTier2()
			-- IncludeSDKTier3()
			-- IncludeSDKMathlib()
			-- IncludeSDKRaytrace()
			-- IncludeSteamAPI()

			files({
				"./src/**.*"
			})

filter({})
