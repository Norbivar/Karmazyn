#pragma once

namespace Configs
{
	#define CREATE_CONFIG(name, temp, cstr) struct name : public Config { constexpr static const char* getValue() { return cstr; }  typedef temp type;   }
		

	class Config
	{
		Config() = default;
		constexpr static const char* getValue()
		{
			return "UNKOWN";
		}
	};

	CREATE_CONFIG(FileLoggingEnabled, bool,  "log_to_file");
	CREATE_CONFIG(LogLevel,           int,   "log_level");

	CREATE_CONFIG(ResolutionX,        int,   "render_x");
	CREATE_CONFIG(ResolutionY,        int,   "render_y");
	CREATE_CONFIG(VSync,              bool,  "debug1");
	CREATE_CONFIG(FrameRateCap,       int,   "maxfps");
	CREATE_CONFIG(RenderWindowStyle,  int,   "renderwindowstyle");

	//DEBUG configs:
	CREATE_CONFIG(PlusTickCount, int, "debug1");
	#undef CREATE_CONFIG
}